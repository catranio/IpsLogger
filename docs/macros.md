## Register custom log functions

This macro allows you to register logging functions for a specific id.\
You can use function:\
`ipslog_gen_funcs(some);`\
`ipslog_gen_funcs(some, severity, SEVERITY);`

## Example

This code:

```c++
ipslog_gen_funcs(some);
```

expand:

```c++
namespace ips::logger {
inline Recorder some_fatal(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::kFatal, level};
}
};  // namespace ips::logger
namespace ips::logger {
inline Recorder some_error(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::kError, level};
}
};  // namespace ips::logger
namespace ips::logger {
inline Recorder some_warning(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::kWarning, level};
}
};  // namespace ips::logger
namespace ips::logger {
inline Recorder some_info(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::kInfo, level};
}
};  // namespace ips::logger
namespace ips::logger {
inline Recorder some_trace(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::kTrace, level};
}
};  // namespace ips::logger
namespace ips::logger {
inline Recorder some_debug(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::kDebug, level};
}
};  // namespace ips::logger
```