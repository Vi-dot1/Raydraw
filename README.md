# RayDraw
A small paint like drawing program made entirely in C++ using only Raylib (and RayGui for User Interface in the future). The point of RayDraw is to be simple to use, with everything being bundled as a single binary with no extra dependencies attached.

# Compiling
Once cloned the project is required to populate the submodules in git:
```bash
git submodule update --init --recursive
```

After dependencies are fetch it can be compiled using only `cmake` as long as you have a C++ compiler installed:
```bash
mkdir build
cd build
cmake -S .. -B
cmake --build .
```

The built binary should be inside `build/Raydraw/` after compilation finishes
