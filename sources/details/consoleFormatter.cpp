#include "consoleFormatter.hpp"

#include <fmt/color.h>
#include <fmt/format.h>

#include <ips/logger/definitions.hpp>
#include <ips/logger/recorder.hpp>

#include "dateFormatter.hpp"
#include "utils.hpp"

namespace ips::logger::details {

void ConsoleFormatter::fmt(const Recorder& recorder,
                           std::string& dest) const noexcept {
  auto color = fmt::color::light_gray;

  const auto severity = recorder.getSeverity();
  using enum Severity;
  using enum fmt::color;
  if (severity == kFatal || severity == kError) {
    color = indian_red;
  } else if (severity == kWarning) {
    color = dark_golden_rod;
  } else if (severity == kInfo) {
    color = cornflower_blue;
  } else if (severity == kTrace) {
    color = light_gray;
  } else if (severity == kDebug) {
    color = dim_gray;
  }

  const auto datetime = utils::to_string(recorder.getTimestamp());
  const auto location = recorder.getSourceLocation();
  std::string_view filename = location.file_name();
  filename.remove_prefix(filename.find_last_of('/') + 1);
  fmt::format_to(
      std::back_inserter(dest), "{} {}\n",
      fmt::format(fg(color), "[{}|{}({})|{}]", datetime, filename,
                  location.line(), to_string(recorder.getSeverity())),
      recorder.getBuffer());
}

}  // namespace ips::logger::details
