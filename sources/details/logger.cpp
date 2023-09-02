#include "logger.hpp"

namespace ips::logger::details {

Logger::Logger(std::string_view id, Severity severity, writer_t&& writer,
               formatter_t&& formatter, level_t maxLevel,
               SeverityEqualMode severityEqualMode)
    : severity_(severity),
      severityEqualMode_(severityEqualMode),
      maxLevel_(maxLevel),
      id_(id),
      writer_(std::move(writer)),
      formatter_(std::move(formatter)) {}

Severity Logger::getSeverity() const noexcept { return severity_; }

Logger::SeverityEqualMode Logger::getSeverityEqualMode() const noexcept {
  return severityEqualMode_;
}

level_t Logger::getMaxLevel() const noexcept { return maxLevel_; }

std::string_view Logger::getId() const noexcept { return id_; }

Writer& Logger::getWriter() const noexcept { return *writer_; }

const Formatter& Logger::getFormatter() const noexcept { return *formatter_; }

}  // namespace ips::logger::details
