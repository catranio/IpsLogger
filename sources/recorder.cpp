
#include "ips/logger/recorder.hpp"
#include "details/storageLoggers.hpp"

#include <chrono>

#include <fmt/format.h>

using namespace ips::logger;

constexpr static std::size_t kBufferSize = 1024;

Recorder::Recorder(Severity severity, level_t level, id_t id) :
        severity_(severity),
        level_(level),
        id_(id),
        name_(),
        buffer_() {
    buffer_.reserve(kBufferSize);
    timestamp_ = std::chrono::system_clock::now().time_since_epoch().count();
}

Recorder::Recorder(const name_t& name, level_t level, id_t id) :
        severity_(Severity::NONE),
        level_(level),
        id_(id),
        name_(name),
        buffer_() {
    buffer_.reserve(kBufferSize);
    timestamp_ = std::chrono::system_clock::now().time_since_epoch().count();
}


Recorder::~Recorder() {
    details::StorageLoggers::write(*this);
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
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{:g}"), value);
    return *this;
}

Recorder& Recorder::operator<<(long double value) noexcept {
    fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{:g}"), value);
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

ips::logger::Recorder::timestamp_t Recorder::getTimestamp() const noexcept {
    return timestamp_;
}

Severity Recorder::getSeverity() const noexcept {
    return severity_;
}

level_t Recorder::getLevel() const noexcept {
    return level_;
}

Recorder::name_t Recorder::getName() const noexcept {
    return name_;
}

std::string_view Recorder::getBuffer() const noexcept {
    return buffer_.data();
}

id_t Recorder::getLoggerId() const noexcept {
    return id_;
}
