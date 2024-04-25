#include "logger.hpp"

namespace ips::logger::details {

Logger::Logger(const Id id, const Severity severity, WriterSptr&& writer,
               FormatterSptr&& formatter, const Level maxLevel,
               const SeverityEqualMode severityEqualMode)
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

Level Logger::getMaxLevel() const noexcept { return maxLevel_; }

std::string_view Logger::getId() const noexcept { return id_; }

Writer& Logger::getWriter() const noexcept { return *writer_; }

const Formatter& Logger::getFormatter() const noexcept { return *formatter_; }

}  // namespace ips::logger::details
