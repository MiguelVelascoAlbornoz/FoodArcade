# FoodArcade

FoodArcade is a high school arcade project featuring several classic minigames, OpenGL graphics, and sound, all written in C++.

## Features
- Multiple arcade minigames in a single executable
- Hardware-accelerated graphics (OpenGL)
- GUI with ImGui
- Integrated sound using miniaudio

## Requirements
- Windows
- Python 3.x
- g++ and gcc in your system PATH (MinGW recommended)
- No need to install external dependencies: everything is included in the `external/` folder

## Build Instructions
To build, run:
```
python launch.py release
```
or
```
python launch.py debug
```

## External Dependencies Licenses
All included libraries (GLFW, GLM, GLEW, ImGui, stb, miniaudio) use permissive licenses. See [external/LICENSES.md](external/LICENSES.md) for details.

---

Contributions and suggestions are welcome!
