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
  return Recorder{"some", Severity::FATAL, level};
}
};  // namespace ips::logger
namespace ips::logger {
inline Recorder some_error(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::ERROR, level};
}
};  // namespace ips::logger
namespace ips::logger {
inline Recorder some_warning(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::WARNING, level};
}
};  // namespace ips::logger
namespace ips::logger {
inline Recorder some_info(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::INFO, level};
}
};  // namespace ips::logger
namespace ips::logger {
inline Recorder some_trace(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::TRACE, level};
}
};  // namespace ips::logger
namespace ips::logger {
inline Recorder some_debug(level_t level = kLevelDefault) {
  return Recorder{"some", Severity::DEBUG, level};
}
};  // namespace ips::logger
```