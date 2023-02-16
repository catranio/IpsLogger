
#include <ips/logger/recorder.hpp>

#include <fmt/format.h>

using namespace ips::logger;

constexpr static size_t kBufferSize = 1024;

Recorder::Recorder(Severity severity, level_t level, id_t id) :
        severity_(severity),
        level_(level),
        id_(id),
        buffer_() {
    buffer_.reserve(kBufferSize);
    timestamp_ = std::chrono::system_clock::now().time_since_epoch();
}


Recorder::~Recorder() {

}

Recorder& Recorder::operator<<(char value) noexcept {
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
    return *this;
}

Recorder& Recorder::operator<<(std::string_view value) noexcept {
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
    return *this;
}

Recorder& Recorder::operator<<(float value) noexcept {
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
    return *this;
}

Recorder& Recorder::operator<<(double value) noexcept {
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
    return *this;
}

Recorder& Recorder::operator<<(long double value) noexcept {
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
    return *this;
}

Recorder& Recorder::operator<<(unsigned long long value) noexcept {
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
    return *this;
}

Recorder& Recorder::operator<<(long long value) noexcept {
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
    return *this;
}

Recorder& Recorder::operator<<(bool value) noexcept {
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value ? "true" : "false");
    return *this;
}

Recorder& Recorder::operator<<(const std::exception& value) noexcept {
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value.what());
    return *this;
}

auto Recorder::getTimestamp() const noexcept {
    return timestamp_;
}

constexpr Severity Recorder::getSeverity() const noexcept {
    return severity_;
}

constexpr level_t Recorder::getLevel() const noexcept {
    return level_;
}

std::string Recorder::getBuffer() const noexcept {
    return fmt::to_string(buffer_);
}
