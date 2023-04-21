#include "ips/logger/log.hpp"
#include "details/storage.hpp"
#include "details/dateFormatter.hpp"
#include "details/fileWriter.hpp"

using namespace ips::logger;

[[maybe_unused]] void ips::logger::init(const id_t& id, const std::string& filename,
                                 Severity severity, level_t maxLevel) noexcept {
	details::Storage::instance().add(details::Logger{id, severity,
									 std::make_unique<details::FileWriter>(filename),
									 std::make_unique<details::DateFormatter>(),
									  maxLevel});
}

Recorder ips::logger::log(const id_t& id, Severity severity, level_t level) noexcept {
    return Recorder{id, severity, level};
}

[[maybe_unused]] Recorder ips::logger::fatal(const id_t& id, level_t level) noexcept {
    return log(id, Severity::FATAL, level);
}

[[maybe_unused]] Recorder ips::logger::error(const id_t& id, level_t level) noexcept {
    return log(id, Severity::ERROR, level);
}

[[maybe_unused]] Recorder ips::logger::warning(const id_t& id, level_t level) noexcept {
    return log(id, Severity::WARNING, level);
}

[[maybe_unused]]Recorder ips::logger::info(const id_t& id, level_t level) noexcept {
    return log(id, Severity::INFO, level);
}

[[maybe_unused]] Recorder ips::logger::trace(const id_t& id, level_t level) noexcept {
    return log(id, Severity::TRACE, level);
}

[[maybe_unused]] Recorder ips::logger::debug(const id_t& id, level_t level) noexcept {
    return log(id, Severity::DEBUG, level);
}
