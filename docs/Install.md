## Dependencies for assembly
* Compiler with c++17 support.
* CMake version 3.11 or later.

The assembly process is fully automated. Dependencies are pumped out via FetchContent.

## Dependencies used in the project
[fmt](https://github.com/fmtlib/fmt) -  is an open-source formatting library. \
[IpsCMakeModules](https://github.com/catranio/IpsCMakeModules) - a set of cmake functions to facilitate the writing of build scripts.

## Example of build
```console
$ git clone https://github.com/catranio/IpsLogger.git
$ cd IpsLogger && mkdir build && cd build
$ cmake .. && make -j
```
