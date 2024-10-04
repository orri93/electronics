#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define DELAY_TIME 1000

#define SEALEVELPRESSURE_HPA (1013.25)


/* Wiring

  ESP32         BME280
  MOSI  D11     SDI
  MISO  D12     SDO
  SCKL  D13     SCK
  CS    D10     CS

*/


Adafruit_BME280 bme(SS);


unsigned status;


void report();


void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("ESP32 BME280");


  Serial.print("MOSI: ");
  Serial.println(MOSI);
  Serial.print("MISO: ");
  Serial.println(MISO);
  Serial.print("SCK: ");
  Serial.println(SCK);
  Serial.print("SS: ");
  Serial.println(SS);


  pinMode(SS, OUTPUT);


  status = bme.begin();


  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
}


void loop() {
  delay(DELAY_TIME);
  report();
}


void report() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");


  Serial.print("Pressure = ");


  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");


  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");


  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");


  Serial.println();
}

