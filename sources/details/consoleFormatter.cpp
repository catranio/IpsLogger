#include "consoleFormatter.hpp"
#include <ips/logger/recorder.hpp>
#include <ips/logger/definitions.hpp>

#include <fmt/format.h>
#include <fmt/color.h>

using namespace ips::logger::details;

std::string ConsoleFormatter::fmt(const Recorder &recorder) const noexcept {
	auto res = DateFormatter::fmt(recorder);

	fmt::color color;
	switch (recorder.getSeverity()) {
		case Severity::FATAL:
		case Severity::ERROR: color = fmt::color::indian_red; break;
		case Severity::WARNING: color = fmt::color::dark_golden_rod; break;
		case Severity::INFO: color = fmt::color::cornflower_blue; break;
		case Severity::TRACE: color = fmt::color::light_gray; break;
		case Severity::DEBUG: color = fmt::color::dim_gray; break;
		default: color = fmt::color::white; break;
	}
	return fmt::format( fg(color), FMT_STRING("{}"), res);
}