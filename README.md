# RayDraw
A small paint like drawing program made entirely in C++ using only Raylib and RayGui for User Interface. The point of RayDraw is to be simple to use, with everything being bundled as a single binary with no extra dependencies attached.

# Compiling
Once cloned the project is required to populate the git submodules:
```bash
git submodule update --init --recursive
```

After dependencies are fetch it can be build with `cmake`:
```bash
mkdir build
cd build
cmake -S .. -B
cmake --build .
```

The built binary should be inside `build/Raydraw/` after compilation finishes

## Webassembly

It is also possible to configure the project to be build as webassembly using Emscripten, using the `wasm` preset in `CMakePresets.json` 
```Bash
cmake --preset wasm
```
It is still a work in progress since it tends to crash when the window is resized, it also assumes you have the [emscripten toolchain](https://emscripten.org/) installed on your machine
