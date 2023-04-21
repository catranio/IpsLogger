#include "logger.hpp"

using namespace ips::logger;
using namespace ips::logger::details;

Logger::Logger(std::string_view id,
	   Severity severity,
	   writer_t&& writer,
	   formatter_t&& formatter,
	   level_t maxLevel,
	   SeverityEqualMode severityEqualMode) :
	   severity_(severity),
	   severityEqualMode_(severityEqualMode),
	   maxLevel_(maxLevel),
	   id_(id),
	   writer_(std::move(writer)),
	   formatter_(std::move(formatter)) {
}

Logger::Logger(Logger&& logger) noexcept {
	id_ = std::move(logger.id_);
	severity_ = logger.severity_;
	maxLevel_ = logger.maxLevel_;
	severityEqualMode_ = logger.severityEqualMode_;
	writer_ = std::move(logger.writer_);
	formatter_ = std::move(logger.formatter_);
}

Logger& Logger::operator=(Logger &&logger) noexcept {
	if (this != &logger) {
		id_ = std::move(logger.id_);
		severity_ = logger.severity_;
		maxLevel_ = logger.maxLevel_;
		severityEqualMode_ = logger.severityEqualMode_;
		writer_ = std::move(logger.writer_);
		formatter_ = std::move(logger.formatter_);
	}
	return *this;
}

Severity Logger::getSeverity() const noexcept {
	return severity_;
}

Logger::SeverityEqualMode Logger::getSeverityEqualMode() const noexcept {
	return severityEqualMode_;
}

level_t Logger::getMaxLevel() const noexcept {
	return maxLevel_;
}

std::string_view Logger::getId() const noexcept {
	return id_;
}

Writer& Logger::getWriter() const noexcept {
	return *writer_;
}

const Formatter& Logger::getFormatter() const noexcept {
	return *formatter_;
}
