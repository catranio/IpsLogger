#include "ips/logger/log.hpp"
#include "details/storageLoggers.hpp"
#include "details/dateFormatter.hpp"
#include "details/fileWriter.hpp"

using namespace ips::logger;

[[maybe_unused]] void ips::logger::init(const std::string& filename,
                                 Severity severity, level_t level, id_t id) noexcept {
    details::StorageLoggers::add(id, level, severity,
                                std::make_unique<details::FileWriter>(filename),
                                std::make_unique<details::DateFormatter>());
}

[[maybe_unused]] inline void ips::logger::uninit(id_t id) noexcept {
    details::StorageLoggers::remove(id);
}

Recorder ips::logger::log(Severity severity, level_t level, id_t id) noexcept {
    return Recorder{severity, level, id};
}

[[maybe_unused]] Recorder ips::logger::fatal(level_t level, id_t id) noexcept {
    return log(Severity::FATAL, level, id);
}

[[maybe_unused]] Recorder ips::logger::error(level_t level, id_t id) noexcept {
    return log(Severity::ERROR, level, id);
}

[[maybe_unused]] Recorder ips::logger::warning(level_t level, id_t id) noexcept {
    return log(Severity::WARNING, level, id);
}

[[maybe_unused]]Recorder ips::logger::info(level_t level, id_t id) noexcept {
    return log(Severity::INFO, level, id);
}

[[maybe_unused]] Recorder ips::logger::trace(level_t level, id_t id) noexcept {
    return log(Severity::TRACE, level, id);
}

[[maybe_unused]] Recorder ips::logger::debug(level_t level, id_t id) noexcept {
    return log(Severity::DEBUG, level, id);
}
