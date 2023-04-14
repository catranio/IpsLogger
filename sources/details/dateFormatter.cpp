#include "dateFormatter.hpp"
#include <ips/logger/recorder.hpp>
#include <ips/logger/definitions.hpp>

#include <fmt/format.h>
#include <fmt/chrono.h>

using namespace ips::logger::details;

std::string DateFormatter::fmt(const Recorder &recorder) noexcept {
	std::chrono::microseconds mc(recorder.getTimestamp());
	auto tp = std::chrono::time_point<std::chrono::system_clock>(mc);
    return fmt::format("[{:%Y.%m.%d %H:%M:}{:%S}] {}({}): {}\n",
					   tp, mc,
                       ips::logger::to_string(recorder.getSeverity()),
                       recorder.getLevel(),
                       recorder.getBuffer());
}