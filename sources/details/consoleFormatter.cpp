#include "consoleFormatter.hpp"

#include <fmt/color.h>
#include <fmt/format.h>

#include <ips/logger/definitions.hpp>
#include <ips/logger/recorder.hpp>

namespace ips::logger::details {

std::string ConsoleFormatter::fmt(const Recorder& recorder) const noexcept {
  auto res = DateFormatter::fmt(recorder);

  fmt::color color;
  switch (recorder.getSeverity()) {
    using enum Severity;
    using enum fmt::color;

    case kFatal:
    case kError:
      color = indian_red;
      break;
    case kWarning:
      color = dark_golden_rod;
      break;
    case kInfo:
      color = cornflower_blue;
      break;
    case kTrace:
      color = light_gray;
      break;
    case kDebug:
      color = dim_gray;
      break;
    default:
      color = white;
      break;
  }
  return fmt::format(fg(color), FMT_STRING("{}"), res);
}

}  // namespace ips::logger::details
