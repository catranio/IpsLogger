#include "dateFormatter.hpp"

#include <fmt/format.h>

#include <ips/logger/definitions.hpp>
#include <ips/logger/recorder.hpp>

#include "utils.hpp"

namespace ips::logger::details {

std::string DateFormatter::fmt(const Recorder& recorder) const noexcept {
  std::string buffer;
  buffer.reserve(recorder.getBuffer().size() + 32);
  fmt::format_to(std::back_inserter(buffer), "[{}|{}] ",
                 utils::to_string(recorder.getTimestamp()),
                 to_string(recorder.getSeverity()));
  buffer += recorder.getBuffer() + "\n";
  return buffer;
}

}  // namespace ips::logger::details
