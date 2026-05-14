/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Geirmundur Orri Sigurdsson
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 Geirmundur Orri Sigurdsson.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

/* STM32C0 register base addresses (AHB/APB mapped peripherals). */
#define RCC_BASE        (0x40021000UL)
#define GPIOA_BASE      (0x50000000UL)
#define GPIOB_BASE      (0x50000400UL)

/* Register offsets. */
#define RCC_IOPENR_OFF  (0x34UL)
#define GPIO_MODER_OFF  (0x00UL)
#define GPIO_BSRR_OFF   (0x18UL)

/* Register access helpers. */
#define REG32(addr)     (*(volatile uint32_t *)(addr))

#define RCC_IOPENR      REG32(RCC_BASE + RCC_IOPENR_OFF)
#define GPIOA_MODER     REG32(GPIOA_BASE + GPIO_MODER_OFF)
#define GPIOA_BSRR      REG32(GPIOA_BASE + GPIO_BSRR_OFF)
#define GPIOB_MODER     REG32(GPIOB_BASE + GPIO_MODER_OFF)
#define GPIOB_BSRR      REG32(GPIOB_BASE + GPIO_BSRR_OFF)

/* GPIO clock bits. */
#define RCC_IOPENR_GPIOAEN   (1UL << 0)
#define RCC_IOPENR_GPIOBEN   (1UL << 1)

typedef struct
{
  volatile uint32_t *bsrr;
  uint8_t pin;
} LedPin;

/* LEDs from compass.md mapping:
 * PA2..PA12, PA15, PB0..PB3
 */
static const LedPin kLedPins[] = {
  { &GPIOA_BSRR, 2 },
  { &GPIOA_BSRR, 3 },
  { &GPIOA_BSRR, 4 },
  { &GPIOA_BSRR, 5 },
  { &GPIOA_BSRR, 6 },
  { &GPIOA_BSRR, 7 },
  { &GPIOA_BSRR, 8 },
  { &GPIOA_BSRR, 9 },
  { &GPIOA_BSRR, 10 },
  { &GPIOA_BSRR, 11 },
  { &GPIOA_BSRR, 12 },
  { &GPIOA_BSRR, 15 },
  { &GPIOB_BSRR, 0 },
  { &GPIOB_BSRR, 1 },
  { &GPIOB_BSRR, 2 },
  { &GPIOB_BSRR, 3 },
};

#define LED_STEP_DELAY_CYCLES (2000000UL)

static void delay_cycles(volatile uint32_t cycles)
{
  while (cycles-- > 0U)
  {
    __asm volatile ("nop");
  }
}

static void led_gpio_init(void)
{
  /* Enable peripheral clocks for GPIOA/GPIOB. */
  RCC_IOPENR |= RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN;

  /* Configure PA2..PA12 and PA15 as outputs (01b in MODER). */
  for (uint8_t pin = 2U; pin <= 12U; ++pin)
  {
    GPIOA_MODER &= ~(0x3UL << (pin * 2U));
    GPIOA_MODER |=  (0x1UL << (pin * 2U));
  }
  GPIOA_MODER &= ~(0x3UL << (15U * 2U));
  GPIOA_MODER |=  (0x1UL << (15U * 2U));

  /* Configure PB0..PB3 as outputs. */
  for (uint8_t pin = 0U; pin <= 3U; ++pin)
  {
    GPIOB_MODER &= ~(0x3UL << (pin * 2U));
    GPIOB_MODER |=  (0x1UL << (pin * 2U));
  }
}

static void led_all_off(void)
{
  GPIOA_BSRR =
    (1UL << (2U + 16U)) |
    (1UL << (3U + 16U)) |
    (1UL << (4U + 16U)) |
    (1UL << (5U + 16U)) |
    (1UL << (6U + 16U)) |
    (1UL << (7U + 16U)) |
    (1UL << (8U + 16U)) |
    (1UL << (9U + 16U)) |
    (1UL << (10U + 16U)) |
    (1UL << (11U + 16U)) |
    (1UL << (12U + 16U)) |
    (1UL << (15U + 16U));

  GPIOB_BSRR =
    (1UL << (0U + 16U)) |
    (1UL << (1U + 16U)) |
    (1UL << (2U + 16U)) |
    (1UL << (3U + 16U));
}

static void led_on(const LedPin *led)
{
  *(led->bsrr) = (1UL << led->pin);
}

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
  led_gpio_init();
  led_all_off();

  for (;;)
  {
    for (uint32_t i = 0U; i < (sizeof(kLedPins) / sizeof(kLedPins[0])); ++i)
    {
      led_all_off();
      led_on(&kLedPins[i]);
      delay_cycles(LED_STEP_DELAY_CYCLES);
    }
  }
}
