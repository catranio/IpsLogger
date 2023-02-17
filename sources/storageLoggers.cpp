#include <ips/logger/ditails/storageLoggers.hpp>
#include <ips/logger/writer.hpp>
#include <ips/logger/formatter.hpp>
#include <ips/logger/recorder.hpp>

#include <iostream>

using namespace ips::logger::detail;

void StorageLoggers::add(id_t id, level_t maxLevel, Severity severity,
                std::unique_ptr<Writer>&& writer, std::unique_ptr<Formatter>&& formatter) noexcept {
    auto& instance = StorageLoggers::instance();
    std::unique_lock lock(instance.mutex_);
    instance.storage_.emplace(id, SettingsLoggger{maxLevel, severity,
                                   std::move(writer),
                                   std::move(formatter)});
}

void StorageLoggers::remove(id_t id) noexcept {
    auto& instance = StorageLoggers::instance();
    std::unique_lock lock(instance.mutex_);
    instance.storage_.erase(id);
}

bool StorageLoggers::write(const Recorder& recorder) noexcept {
    auto& instance = StorageLoggers::instance();
    std::unique_lock lock(instance.mutex_);
    const auto it = instance.storage_.find(recorder.getLoggerId());
    if (it == instance.storage_.end()) {
        return false;
    }

    const auto& settings = it->second;
    if (!isWrite(recorder, settings)) {
        return false;
    }

    const auto str = settings.formatter->fmt(recorder);
    settings.writer->write(str);
    return true;
}

StorageLoggers& StorageLoggers::instance() noexcept {
    static StorageLoggers instance;
    return instance;
}

bool StorageLoggers::isWrite(const Recorder& recorder, const SettingsLoggger& settings) noexcept {
    return (settings.severity == Severity::ALL
        || recorder.getSeverity() == settings.severity)
        && recorder.getLevel() <= settings.maxLevel;
}