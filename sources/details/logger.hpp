#ifndef IPSLOGGER_DETAILS_LOGGER_HPP
#define IPSLOGGER_DETAILS_LOGGER_HPP

#include <ips/logger/definitions.hpp>
#include <ips/logger/formatter.hpp>
#include <ips/logger/writer.hpp>
#include <memory>

namespace ips::logger::details {
class Logger {
 public:
  enum class SeverityEqualMode : std::uint8_t {
    kStrong,
    kRange,
  };

  using WriterSptr = std::shared_ptr<Writer>;
  using FormatterSptr = std::shared_ptr<Formatter>;

  Logger(Id id, Severity severity, WriterSptr&& writer,
         FormatterSptr&& formatter, Level maxLevel = 10,
         SeverityEqualMode severityEqualMode = SeverityEqualMode::kRange);

  [[nodiscard]] Severity getSeverity() const noexcept;
  [[nodiscard]] SeverityEqualMode getSeverityEqualMode() const noexcept;
  [[nodiscard]] Level getMaxLevel() const noexcept;
  [[nodiscard]] std::string_view getId() const noexcept;
  [[nodiscard]] Writer& getWriter() const noexcept;
  [[nodiscard]] const Formatter& getFormatter() const noexcept;

 private:
  Severity severity_;
  SeverityEqualMode severityEqualMode_;
  Level maxLevel_;
  Id id_;
  WriterSptr writer_;
  FormatterSptr formatter_;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_LOGGER_HPP */
