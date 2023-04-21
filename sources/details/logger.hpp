#ifndef IPSLOGGER_DETAILS_LOGGER_HPP
#define IPSLOGGER_DETAILS_LOGGER_HPP

#include <ips/logger/definitions.hpp>
#include <ips/logger/writer.hpp>
#include <ips/logger/formatter.hpp>
#include <ips/logger/recorder.hpp>

#include <string>
#include <memory>

namespace ips::logger::details {
	class Logger {
	public:
		enum class SeverityEqualMode {
			STRONG,
			RANGE,
		};

		using writer_t = std::unique_ptr<Writer>;
		using formatter_t = std::unique_ptr<Formatter>;

	public:
		Logger(std::string_view id,
			   Severity severity,
			   writer_t&& writer,
			   formatter_t&& formatter,
			   level_t maxLevel = 10,
			   SeverityEqualMode severityEqualMode = SeverityEqualMode::RANGE);
		Logger(Logger&& logger) noexcept;
		Logger& operator=(Logger&& logger) noexcept;

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
}

#endif /* IPSLOGGER_DETAILS_LOGGER_HPP */
