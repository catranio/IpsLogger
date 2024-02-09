#include "dateFormatter.hpp"

#include <fmt/format.h>

#include <ips/logger/definitions.hpp>
#include <ips/logger/recorder.hpp>

#include "utils.hpp"

namespace ips::logger::details {

void DateFormatter::fmt(const Recorder& recorder,
                        std::string& dest) const noexcept {
  const auto datetime = utils::to_string(recorder.getTimestamp());
  const auto severity = to_string(recorder.getSeverity());
  dest.reserve(recorder.getBuffer().size() + severity.size() + datetime.size());
  dest += "[";
  dest += datetime;
  dest += "|";
  dest += severity;
  dest += "] ";
  dest += recorder.getBuffer() + "\n";
}

}  // namespace ips::logger::details
