#ifndef IPSLOGGER_DEFINITIONS_HPP
#define IPSLOGGER_DEFINITIONS_HPP

#include <cstdint>
#include <iosfwd>
#include <string_view>

namespace ips::logger {
enum class Severity : std::uint8_t {
  kNone,
  kFatal,
  kError,
  kWarning,
  kInfo,
  kTrace,
  kDebug,
  kAll,
};

using Level = unsigned;
using Id = std::string_view;
using Seconds = unsigned;

constexpr static Level kMaxLevelDefault = 10;
constexpr static Level kLevelDefault = 3;
constexpr static std::string_view kConsoleId = "__ips_console_id__";
constexpr static Seconds kTimeRotateDefault = 0;

constexpr std::string_view to_string(const Severity severity) noexcept {
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
