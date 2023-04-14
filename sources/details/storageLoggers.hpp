#ifndef IPSLOGGER_DETAILS_STORAGELOGGERS_HPP
#define IPSLOGGER_DETAILS_STORAGELOGGERS_HPP

#include "ips/logger/definitions.hpp"

#include <mutex>
#include <unordered_map>
#include <vector>
#include <memory>

namespace ips::logger {
    class Recorder;
    class Formatter;
    class Writer;
}

namespace ips::logger::details
{
    class StorageLoggers {
    private:
        struct SettingsLogger {
            level_t maxLevel;
            Severity severity;
            std::string name;
            std::unique_ptr<Writer> writer;
            std::unique_ptr<Formatter> formatter;
        };

    public:
        static void add(id_t id, level_t maxLevel, Severity severity,
                        std::unique_ptr<Writer>&& writer, std::unique_ptr<Formatter>&& formatter) noexcept;
        static void add(id_t id, level_t maxLevel, const std::string& name,
                        std::unique_ptr<Writer>&& writer, std::unique_ptr<Formatter>&& formatter) noexcept;
        static bool remove(id_t id, Severity severity) noexcept;
        static bool remove(id_t id, const std::string& name) noexcept;
        static bool write(const Recorder& recorder) noexcept;

    private:
        StorageLoggers() = default;
        static StorageLoggers& instance() noexcept;
        static bool isWrite(const Recorder& recorder, const SettingsLogger& settings) noexcept;

        static void add(id_t id, level_t maxLevel,
                        Severity severity, const std::string& name,
                        std::unique_ptr<Writer>&& writer,
                        std::unique_ptr<Formatter>&& formatter) noexcept;
        static bool remove(id_t id, Severity severity, const std::string& name) noexcept;

    public:
        StorageLoggers(const StorageLoggers&) = delete;
        StorageLoggers(StorageLoggers&&) = delete;
        StorageLoggers& operator=(const StorageLoggers&) = delete;
        StorageLoggers&& operator=(StorageLoggers&&) = delete;

    private:
        using mutex_t = std::mutex;
        using storage_t = std::unordered_map<id_t, std::vector<SettingsLogger>>;

        mutex_t mutex_;
        storage_t storage_;
    };
}

#endif /* IPSLOGGER_DETAILS_STORAGELOGGERS_HPP */
