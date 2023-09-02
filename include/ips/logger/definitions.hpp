#ifndef IPSLOGGER_DEFINITIONS_HPP
#define IPSLOGGER_DEFINITIONS_HPP

#include <iosfwd>
#include <string_view>

namespace ips::logger {
enum class Severity {
  kNone,
  kFatal,
  kError,
  kWarning,
  kInfo,
  kTrace,
  kDebug,
  kAll,
};

using level_t = unsigned;
using id_t = std::string;
using seconds_t = unsigned;

constexpr static level_t kMaxLevelDefault = 10;
constexpr static level_t kLevelDefault = 3;
constexpr static const char* kConsoleId = "__ips_console_id__";
constexpr static seconds_t kTimeRotateDefault = 0;

constexpr std::string_view to_string(Severity severity) noexcept {
  using enum Severity;
  switch (severity) {
    case kFatal:
      return "fatal";
    case kError:
      return "error";
    case kWarning:
      return "warning";
    case kInfo:
      return "info";
    case kTrace:
      return "trace";
    case kDebug:
      return "debug";
    case kAll:
      return "all";
    case kNone:
      return "none";
    default:
      return "";
  }
}
}  // namespace ips::logger

#endif /* IPSLOGGER_DEFINITIONS_HPP */
