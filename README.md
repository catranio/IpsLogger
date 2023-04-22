# IpsLogger

[![linux](https://github.com/catranio/IpsLogger/actions/workflows/linux.yml/badge.svg)](https://github.com/catranio/IpsLogger/actions/workflows/linux.yml)&nbsp;
[![macos](https://github.com/catranio/IpsLogger/actions/workflows/macos.yml/badge.svg)](https://github.com/catranio/IpsLogger/actions/workflows/macos.yml)&nbsp;

Very fast, compilable, C++ logging library. \
Uses [fmt](https://github.com/fmtlib/fmt) for formatting.

## Build

```console
$ git clone https://github.com/catranio/IpsLogger.git
$ cd IpsLogger && mkdir build && cd build
$ cmake .. && make -j
```
**Dependencies:** C++17 | CMake 3.11

## Platforms
* Linux
* MacOS

## Features
* Feature rich formatting, using the excellent [fmt](https://github.com/fmtlib/fmt) library.
* Multi/Single threaded loggers.
* Various log targets:
    * File logging.
    * Console logging (colors supported).
* Complete deletion from the executable file when the flag `IPS_LOGGER_ENABLE` is disable.

## Usage samples

### Console logger 
```c++
#include <ips/logger/log.hpp>
int main() 
{
    ips::logger::initConsole(Severity::ALL);
    ips::logger::info() << "some logger string #" << 1;
}
```

### File logger
```c++
#include <ips/logger/log.hpp>

namespace ips::logger {
    inline Recorder custom_trace(level_t level) {
        return Recorder{"logger.id", Severity::TRACE, level};
    }
}

int main() 
{
    ips::logger::init("logger.id", "trace_logger.log", Severity::ALL);
    ips::logger::custom_trace() << "some logger string #" << 1;
}
```

## Documentation
Documentation can be found in the [wiki](https://github.com/catranio/IpsLogger/wiki) pages.

---
Author: *Petr Iaskevich, MIT license*\
Email: *iaskdeveloper@gmail.com*
