#include "ips/logger/log.hpp"
#include "details/storage.hpp"
#include "details/dateFormatter.hpp"
#include "details/fileWriter.hpp"

using namespace ips::logger;

[[maybe_unused]] void ips::logger::init(const std::string& filename,
                                 Severity severity, level_t maxLevel) noexcept {
	details::Storage::instance().add({"some", severity,
									 std::make_unique<details::FileWriter>(filename),
									 std::make_unique<details::DateFormatter>(),
									  maxLevel});
}

Recorder ips::logger::log(Severity severity, level_t level) noexcept {
    return Recorder{"", severity, level};
}

[[maybe_unused]] Recorder ips::logger::fatal(level_t level) noexcept {
    return log(Severity::FATAL, level);
}

[[maybe_unused]] Recorder ips::logger::error(level_t level) noexcept {
    return log(Severity::ERROR, level);
}

[[maybe_unused]] Recorder ips::logger::warning(level_t level) noexcept {
    return log(Severity::WARNING, level);
}

[[maybe_unused]]Recorder ips::logger::info(level_t level) noexcept {
    return log(Severity::INFO, level);
}

[[maybe_unused]] Recorder ips::logger::trace(level_t level) noexcept {
    return log(Severity::TRACE, level);
}

[[maybe_unused]] Recorder ips::logger::debug(level_t level) noexcept {
    return log(Severity::DEBUG, level);
}
