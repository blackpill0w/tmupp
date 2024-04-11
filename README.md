# tmupp
A terminal music player in C++20.
# Dependenies
Cmake will try to download & compile them, but I am not very good with it, so it might fail :)
- [cmake](https://cmake.org) version 3.14 at least.
- [taglib](https://taglib.org) version 2.0-1.2.
# Build
Run this from the root directory of the project.
```bash
mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
```
