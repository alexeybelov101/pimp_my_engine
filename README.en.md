# pimp_my_engine
[Русский](README.md) | **English**

Internal combustion engine process simulator.

## Project status
The project is at an early stage of development. Interfaces and structure may change without prior notice.

## Requirements
Building requires:
- GCC with support for the C++26 standard;
- the nlohmann/json library (header-only, installed separately).

## Building
The project uses a Makefile. The following targets are available:
- make or make release — build an optimized version
- make debug — build a debug version
- make run — build and run
- make debug run — build and run the debug version
- make clean — remove build artifacts

Example:
```bash
make release
./bin/release/pimp_my_engine --config configs/config.json
```

## Usage
Run the simulation with default parameters:
```bash
./bin/release/pimp_my_engine
```

### Available command-line options:
    -t, --time TIME — simulation time in seconds.
    -f, --freq FREQ — simulation frequency in hertz.
    -r, --rpm RPM — initial engine RPM.
    -c, --config PATH — path to the configuration file.
    -h, --help — display help.

## Configuration
Engine and intake/exhaust system parameters are set in a JSON file (default: configs/config.json).
All dimensions are specified in millimeters, mass in grams, and angles in degrees.
The dimensions of the parts in the default config are taken from public sources for the VAZ-21011 engine and may not match those of the actual engine.

## License
The project is distributed under the AGPL-3.0-or-later license. The full license text is available in [COPYING](COPYING).

## TODO:
1. Encapsulate the logic for updating the crankshaft rotation angle.
2. Refactor the project to support modeling various engine layouts (inline, V, W, VR, flat, radial).
3. Calculate flows at junctions of three or more pipes.
4. Implement the throttle valve.
5. Implement the ignition system.
6. Implement the fuel system.
7. Calculate air, fuel, and exhaust gas masses.
8. Implement the combustion process.
9. Parallelize computations.
10. Optimize performance.
11. Create an API for using the project as a library.
12. Implement variable valve timing.
13. Account for crankshaft, connecting rod, and piston inertia.
14. Account for friction.
15. Account for heat release and heat transfer.
16. Implement the cooling system.
17. Implement forced induction systems.
