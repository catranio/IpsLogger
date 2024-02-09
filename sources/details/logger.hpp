#ifndef IPSLOGGER_DETAILS_LOGGER_HPP
#define IPSLOGGER_DETAILS_LOGGER_HPP

#include <ips/logger/definitions.hpp>
#include <ips/logger/formatter.hpp>
#include <ips/logger/recorder.hpp>
#include <ips/logger/writer.hpp>
#include <memory>
#include <string>

namespace ips::logger::details {
class Logger {
 public:
  enum class SeverityEqualMode {
    kStrong,
    kRange,
  };

  using writer_t = std::shared_ptr<Writer>;
  using formatter_t = std::shared_ptr<Formatter>;

  Logger(std::string_view id, Severity severity, writer_t&& writer,
         formatter_t&& formatter, level_t maxLevel = 10,
         SeverityEqualMode severityEqualMode = SeverityEqualMode::kRange);

  [[nodiscard]] Severity getSeverity() const noexcept;
  [[nodiscard]] SeverityEqualMode getSeverityEqualMode() const noexcept;
  [[nodiscard]] level_t getMaxLevel() const noexcept;
  [[nodiscard]] std::string_view getId() const noexcept;
  [[nodiscard]] Writer& getWriter() const noexcept;
  [[nodiscard]] const Formatter& getFormatter() const noexcept;

 private:
  Severity severity_;
  SeverityEqualMode severityEqualMode_;
  level_t maxLevel_;
  id_t id_;
  writer_t writer_;
  formatter_t formatter_;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_LOGGER_HPP */
