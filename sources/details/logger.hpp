#ifndef IPSLOGGER_DETAILS_LOGGER_HPP
#define IPSLOGGER_DETAILS_LOGGER_HPP

#include <ips/logger/definitions.hpp>
#include <ips/logger/writer.hpp>
#include <ips/logger/formatter.hpp>

#include <string>
#include <memory>

namespace ips::logger::details {
	enum class SeverityEqualMode {
		STRONG,
		RANGE,
	};

	class Logger {
	public:
		Logger(std::string_view name,
			   Severity severity,
			   std::unique_ptr<Writer>&& writer,
			   std::shared_ptr<Formatter>&& formatter,
			   level_t maxLevel = 10,
			   SeverityEqualMode severityEqualMode = SeverityEqualMode::STRONG);
		Logger(Logger&& logger);
		Logger&& operator=(Logger&& logger);

		std::string_view getName() const noexcept;
		Severity getSeverity() const noexcept;
		level_t getMaxLevel() const noexcept;
		SeverityEqualMode getSeverityEqualMode() const noexcept;
		const std::unique_ptr<Writer>& getWriter() const noexcept;
		const std::shared_ptr<Formatter>& getFormatter() const noexcept;

	private:
		std::string name_;
		Severity severity_;
		level_t maxLevel_;
		SeverityEqualMode severityEqualMode_;
		std::unique_ptr<Writer> writer_;
		std::shared_ptr<Formatter> formatter_;
	};
}

#endif /* IPSLOGGER_DETAILS_LOGGER_HPP */
