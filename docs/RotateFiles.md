File rotation is only supported on a time basis. \
Time is set in seconds and starts as soon as the log file is created.

## Example

```c++
auto kLevel = 3;
auto kRotateTimeInSeconds = 3600;
ipslog::init::file("__some.id__", "file.name",
                   Severity::kAll, kLevel, kRotateTimeInSeconds);
```

If time is set to `0` (default), file rotation is disabled.