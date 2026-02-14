# The Tale of the Labyrinth

A grid-based strategy game built in C with raylib. Players move toward a goal "lightcore" while placing walls, collecting bonuses, and avoiding hunters.

## Features
- Grid-based board with walls and temporary barriers
- Player vs. hunter movement and turn flow
- Multiple bonuses (extra move, extra walls, board quake, pick-hunter)
- Save/load support via `data/game.dat`
- A* pathfinding utilities for AI movement

## Build (Windows)
This project is configured for CMake and raylib on Windows.

1. Ensure raylib headers and libraries are available under `include/` and `lib/` (see `CMakeLists.txt`).
2. Build with CMake:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

The executable will be generated in `build/`.

## Run
Run the compiled executable from the build output directory. The game will prompt whether to continue a previous session (saved in `data/game.dat`).

## Controls
- `W/A/S/D`: Move selected player
- `Mouse Left Click`: Select a player
- `T` + `Mouse Left Click`: Place a temporary wall (if available)
- `Space`: Skip player move

## Project Layout
- `src/`: C sources (`main.c`, `board.c`, `inputs.c`, `movements.c`, `bonus.c`, `pathfinding.c`)
- `include/`: Project headers and raylib headers
- `assets/`: Game assets
- `assets/pieces/`, `assets/bonus/`, `assets/fonts/`, `assets/audio/`: Asset groups
- `data/`: Save data (`game.dat`)

## Notes
- The build links against `raylib`, `opengl32`, `gdi32`, and `winmm` as configured in `CMakeLists.txt`.
- Assets are loaded with relative paths, so run the executable from a directory that keeps `assets/` and `data/` adjacent to the project root (e.g., run from `build/` which resolves `../assets/...` and `../data/...`).
