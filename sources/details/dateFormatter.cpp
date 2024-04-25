#include "dateFormatter.hpp"

#include <fmt/format.h>

#include <ips/logger/definitions.hpp>
#include <ips/logger/recorder.hpp>

#include "utils.hpp"

namespace ips::logger::details {

void DateFormatter::fmt(const Recorder& recorder,
                        std::string& dest) const noexcept {
  const auto datetime = utils::to_string(recorder.getTimestamp());
  // to longer work
  // const auto datetime = dataChacher_.to_string(recorder.getTimestamp());

  const auto severity = to_string(recorder.getSeverity());
  const auto location = recorder.getSourceLocation();
  std::string_view filename = location.file_name();
  filename.remove_prefix(filename.find_last_of('/') + 1);
  fmt::format_to(std::back_inserter(dest), "[{}|{}({})|{}] ", datetime,
                 filename, location.line(), severity);
  dest.append(recorder.getBuffer().data(),
              recorder.getBuffer().data() + recorder.getBuffer().size());
  dest.append("\n");
}

}  // namespace ips::logger::details
