# Pathfinding project
Pierre Bouffartigues, Enzo Guilmer, Louna Tabbara

## Installation

This project uses [vcpkg](https://vcpkg.io/en/index.html) with a CMake file.

```bash
# install sfml package with vcpkg
vcpkg install sfml
# build the project
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=<path_to_vcpkg_installation>\vcpkg\scripts\buildsystems\vcpkg.cmake
```

### IDE configuration

**CLion:** Add `-DCMAKE_TOOLCHAIN_FILE=<path_to_vcpkg_installation>\vcpkg\scripts\buildsystems\vcpkg.cmake` to your CMake Settings > CMake options.