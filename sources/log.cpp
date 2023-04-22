#include "ips/logger/log.hpp"
#include "details/storage.hpp"
#include "details/dateFormatter.hpp"
#include "details/fileWriter.hpp"
#include "details/consoleFormatter.hpp"
#include "details/streamWriter.hpp"

#include <iostream>

using namespace ips::logger;

[[maybe_unused]] void ips::logger::init::file(const id_t& id, const std::string& filename,
                                 Severity severity, level_t maxLevel) noexcept {
	details::Storage::instance().add(details::Logger{id, severity,
									 std::make_unique<details::FileWriter>(filename),
									 std::make_unique<details::DateFormatter>(),
									  maxLevel});
}

[[maybe_unused]] void ips::logger::init::console(Severity severity, level_t maxLevel) noexcept {
	details::Storage::instance().add(details::Logger{kConsoleId, severity,
													 std::make_unique<details::StreamWriter>(std::cout),
													 std::make_unique<details::ConsoleFormatter>(),
													 maxLevel});
}

Recorder ips::logger::log(Severity severity, level_t level, const id_t& id) noexcept {
    return Recorder{id, severity, level};
}

[[maybe_unused]] Recorder ips::logger::fatal(level_t level, const id_t& id) noexcept {
    return log(Severity::FATAL, level, id);
}

[[maybe_unused]] Recorder ips::logger::error(level_t level, const id_t& id) noexcept {
    return log(Severity::ERROR, level, id);
}

[[maybe_unused]] Recorder ips::logger::warning(level_t level, const id_t& id) noexcept {
    return log(Severity::WARNING, level, id);
}

[[maybe_unused]]Recorder ips::logger::info(level_t level, const id_t& id) noexcept {
    return log(Severity::INFO, level, id);
}

[[maybe_unused]] Recorder ips::logger::trace(level_t level, const id_t& id) noexcept {
    return log(Severity::TRACE, level, id);
}

[[maybe_unused]] Recorder ips::logger::debug(level_t level, const id_t& id) noexcept {
    return log(Severity::DEBUG, level, id);
}
