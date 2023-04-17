#include "logger.hpp"

using namespace ips::logger;
using namespace ips::logger::details;

Logger::Logger(std::string_view name,
	   Severity severity,
	   std::unique_ptr<Writer>&& writer,
	   std::shared_ptr<Formatter>&& formatter,
	   level_t maxLevel,
	   SeverityEqualMode severityEqualMode) :
	   name_(name),
	   severity_(severity),
	   maxLevel_(maxLevel),
	   severityEqualMode_(severityEqualMode),
	   writer_(std::move(writer)),
	   formatter_(formatter)
	   {
	name_ += std::string{} + "." + to_string(severity);
}

Logger::Logger(Logger&& logger) {
	name_ = std::move(logger.name_);
	severity_ = std::move(logger.severity_);
	maxLevel_ = std::move(logger.maxLevel_);
	severityEqualMode_ = std::move(logger.severityEqualMode_);
	writer_ = std::move(logger.writer_);
	formatter_ = std::move(logger.formatter_);
}

Logger &&Logger::operator=(Logger &&logger) {
	std::swap(*this, logger);
	return std::move(*this);
}

std::string_view Logger::getName() const noexcept {
	return name_;
}

Severity Logger::getSeverity() const noexcept {
	return severity_;
}

level_t Logger::getMaxLevel() const noexcept {
	return maxLevel_;
}

SeverityEqualMode Logger::getSeverityEqualMode() const noexcept {
	return severityEqualMode_;
}

const std::unique_ptr<Writer>& Logger::getWriter() const noexcept {
	return writer_;
}

const std::shared_ptr<Formatter>& Logger::getFormatter() const noexcept {
	return formatter_;
}