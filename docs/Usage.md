## Rules of library use
1. Start using all functions with `ipslog::`! This is necessary for erasing from a binary file to work correctly.
2. The logger must be registered before the logger function can be called. Use the library logger or write one yourself.

## Log level
```c++
Severity::NONE;
Severity::FATAL;
Severity::ERROR;
Severity::WARNING;
Severity::INFO;
Severity::TRACE;
Severity::DEBUG;
Severity::ALL;
```

## Init function
### Init file logger
```c++
ipslog::init::file("some.id", "filename", Severity::ALL, 10);
```
**Args:**
1. Id - id of the logger to be registered.
2. Filename - the name of the file into which the logger will be written.
3. Severity - Alloy level.
4. maxLogLevel - maximum alloying level within the Severity level.
   - Default value: 10

**Return value:** void

### Init file console
```c++
ipslog::init::console(Severity::ALL, 10);
```
**Args:**
1. Severity - Alloy level.
2. maxLogLevel - maximum alloying level within the Severity level.
   - Default value: 10

**Return value:** void

## Logger function
### Recoder
An object that heats up the input for output to the log file. \
Writes data when the object is destroyed.

Receives data using the input operator.
```c++
ipslog::Recorder{} << "Some data " << 1;
```

### log
```c++
ipslog::log(Severity::ALL, 10, "some.id") << "Some value " << 1;
```
**Args:**
1. Severity - Alloy level.
2. maxLogLevel - maximum alloying level within the Severity level.
   - Default value: 10
3. Id - id of the logger to be registered.
   - Default value: inner id for use console logger

**Return value:** Recorder

### Custom log function
**Args:**
1. maxLogLevel - maximum alloying level within the Severity level.
   - Default value: 10
2. Id - id of the logger to be registered.
   - Default value: inner id for use console logger

**Return value:** Recorder

#### fatal
```c++
ipslog::fatal(10, "some.id") << "Some value " << 1;
```

#### error
```c++
ipslog::error(10, "some.id") << "Some value " << 1;
```

#### warning
```c++
ipslog::warning(10, "some.id") << "Some value " << 1;
```

#### info
```c++
ipslog::info(10, "some.id") << "Some value " << 1;
```

#### trace
```c++
ipslog::trace(10, "some.id") << "Some value " << 1;
```

#### debug
```c++
ipslog::debug(10, "some.id") << "Some value " << 1;
```

### Register new custom log function
```c++
/* register */
namespace ips::logger {
    inline Recorder cpe_trace(level_t maxLevel) {
        return Recorder{"cpe", Severity::TRACE, maxLevel};
    }
}

/* usage */
ipslog::cpe_trace(10, "some.id") << "Some value " << 1;
```

