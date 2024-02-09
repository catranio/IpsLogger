#include "consoleFormatter.hpp"

#include <fmt/color.h>
#include <fmt/format.h>

#include <ips/logger/definitions.hpp>
#include <ips/logger/recorder.hpp>

#include "utils.hpp"

namespace ips::logger::details {

void ConsoleFormatter::fmt(const Recorder& recorder,
                           std::string& dest) const noexcept {
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

  dest.reserve(recorder.getBuffer().size() + 32);
  fmt::format_to(
      std::back_inserter(dest), "[{}|{}] ",
      utils::to_string(recorder.getTimestamp()),
      fmt::format(fg(color), "{}", to_string(recorder.getSeverity())));
  dest.append(recorder.getBuffer().data(),
              recorder.getBuffer().data() + recorder.getBuffer().size());
  dest.append("\n");
}

}  // namespace ips::logger::details
