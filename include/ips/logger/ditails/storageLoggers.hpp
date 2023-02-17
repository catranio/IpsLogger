#ifndef IPSLOGGER_STORAGELOGGERS_HPP
#define IPSLOGGER_STORAGELOGGERS_HPP

#include <ips/logger/definitions.hpp>

#include <mutex>
#include <unordered_map>
#include <memory>

namespace ips::logger {
    class Recorder;
    class Formatter;
    class Writer;
}

namespace ips::logger::detail
{
    class StorageLoggers {
    private:
        struct SettingsLoggger {
            level_t maxLevel;
            Severity severity;
            std::unique_ptr<Writer> writer;
            std::unique_ptr<Formatter> formatter;
        };

    public:
        static void add(id_t id, level_t maxLevel, Severity severity,
                        std::unique_ptr<Writer>&& writer, std::unique_ptr<Formatter>&& formatter) noexcept;
        static void remove(id_t id) noexcept;
        static bool write(const Recorder& recorder) noexcept;

    private:
        StorageLoggers() = default;
        static StorageLoggers& instance() noexcept;
        static bool isWrite(const Recorder& recorder, const SettingsLoggger& settings) noexcept;

    public:
        StorageLoggers(const StorageLoggers&) = delete;
        StorageLoggers(StorageLoggers&&) = delete;
        StorageLoggers& operator=(const StorageLoggers&) = delete;
        StorageLoggers&& operator=(StorageLoggers&&) = delete;

    private:
        using mutex_t = std::mutex;
        using storage_t = std::unordered_map<id_t, SettingsLoggger>;

        mutex_t mutex_;
        storage_t storage_;
    };
}

#endif /* IPSLOGGER_STORAGELOGGERS_HPP */
