#ifndef IPSLOGGER_RECORDER_HPP
#define IPSLOGGER_RECORDER_HPP

#include "definitions.hpp"

#include <string_view>
#include <exception>
#include <string>

namespace ips::logger
{
    class Recorder final {
    public:
        using timestamp_t = long long;
        using message_buffer_t = std::string;
        using id_t = std::string;

    public:
        Recorder(const id_t& id, Severity severity, level_t leve);
        ~Recorder();

        Recorder(const Recorder&) = delete;
        Recorder(Recorder&&) = delete;
        Recorder& operator=(const Recorder&) = delete;
        Recorder&& operator=(Recorder&&) = delete;

        template<class T>
        Recorder& operator<<(const T& value) {
            if constexpr (std::is_constructible_v<std::string_view, T>) {
                *this << std::string_view{value};
            } else if constexpr (std::is_signed_v<T>) {
                using LongLong = long long;
                *this << LongLong{value};
            } else if constexpr (std::is_unsigned_v<T>) {
                using UnsigndeLongLong = unsigned long long;
                *this << UnsigndeLongLong{value};
            } else if constexpr (std::is_base_of_v<std::exception, T>) {
                *this << static_cast<const std::exception&>(value);
            } else {
                static_assert(!sizeof(T), "Please implement logging for your type.");
            }

            return *this;
        }

        Recorder& operator<<(char value) noexcept;
        Recorder& operator<<(std::string_view value) noexcept;
        Recorder& operator<<(float value) noexcept;
        Recorder& operator<<(double value) noexcept;
        Recorder& operator<<(long double value) noexcept;
        Recorder& operator<<(unsigned long long value) noexcept;
        Recorder& operator<<(long long value) noexcept;
        Recorder& operator<<(bool value) noexcept;
        Recorder& operator<<(const std::exception& value) noexcept;

        [[nodiscard]] timestamp_t getTimestamp() const noexcept;
        [[nodiscard]] Severity getSeverity() const noexcept;
        [[nodiscard]] level_t getLevel() const noexcept;
        [[nodiscard]] id_t getId() const noexcept;
        [[nodiscard]] std::string_view getBuffer() const noexcept;

    private:
        const Severity severity_;
        const level_t level_;
        const id_t id_;
        message_buffer_t buffer_;
        timestamp_t timestamp_;
    };
}

#endif /* IPSLOGGER_RECORDER_HPP */
