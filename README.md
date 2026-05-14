# electronics

A personal collection of electronics projects, experiments, and reusable design assets.

This repository includes circuit designs (mostly KiCad), component libraries, simulation files, prototypes, firmware/code, and supporting documentation. It is organized as a working archive where each project can include one or more of the following:

- Hardware design files (schematics and PCB layouts)
- Build/manufacturing outputs (for example gerbers)
- Notes, references, and datasheets
- Source code or firmware when the project includes programmable parts

## Folder Structure

Top-level folders are grouped by purpose. Common locations include:

- `circuits/`: Main project folders for KiCad designs (schematics/PCBs).
- `doc/`: Documentation, references, datasheets, books, project notes, and how-to material.
- `src/`: Source code and firmware-related project code when applicable.
- `3d/`: 3D models (for example STEP files) used for PCB/mechanical integration.
- `symbols/`: KiCad symbol libraries.
- `footprints/`: KiCad footprint libraries.
- `gerber/`: Generated manufacturing outputs for selected projects.
- `spices/`: SPICE/LTspice simulation files.
- `prototype/`: Early-stage prototypes and exploratory files.
- `projects/`: Additional project work that may not fit the main `circuits/` layout.
- `media/`: Images and other media assets.
- `pcb/`: Standalone PCB-related utilities or adapter boards.
- `tools/`: Tooling and utility resources.
- `repares/`: Repair-related project material.
- `tmp/`: Temporary files.

## Project Organization Notes

Project contents are not always in a single folder. Depending on the project stage and history:

- KiCad circuit files are often located under `circuits/<project-name>/`.
- Documentation can be stored separately under `doc/`.
- Code or firmware is sometimes placed under `src/`.

This split keeps hardware design, documentation, and software concerns organized while still allowing each project to evolve over time.
