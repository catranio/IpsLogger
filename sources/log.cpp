#include <ips/logger/log.hpp>

using namespace ips::logger;

void ips::logger::init(const std::string& filename,
                                 Severity severity, level_t level, id_t id) noexcept {

}

void ips::logger::init(std::ostream& filename,
                                 Severity severity, level_t level, id_t id) noexcept {

}

Recorder ips::logger::log(Severity severity, level_t level, id_t id) noexcept {
    return Recorder{severity, level, id};
}

Recorder ips::logger::fatal(level_t level, id_t id) noexcept {
    return log(Severity::FATAL, level, id);
}

Recorder ips::logger::error(level_t level, id_t id) noexcept {
    return log(Severity::ERROR, level, id);
}

Recorder ips::logger::warning(level_t level, id_t id) noexcept {
    return log(Severity::WARNING, level, id);
}

Recorder ips::logger::info(level_t level, id_t id) noexcept {
    return log(Severity::INFO, level, id);
}

Recorder ips::logger::trace(level_t level, id_t id) noexcept {
    return log(Severity::TRACE, level, id);
}

Recorder ips::logger::debug(level_t level, id_t id) noexcept {
    return log(Severity::DEBUG, level, id);
}
