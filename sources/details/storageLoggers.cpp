#include "storageLoggers.hpp"
#include "ips/logger/writer.hpp"
#include "ips/logger/formatter.hpp"
#include "ips/logger/recorder.hpp"

using namespace ips::logger::details;

void StorageLoggers::add(id_t id, level_t maxLevel, Severity severity,
                std::unique_ptr<Writer>&& writer, std::unique_ptr<Formatter>&& formatter) noexcept {
    return add(id, maxLevel, severity, std::string{}, std::move(writer), std::move(formatter));
}

void StorageLoggers::add(id_t id, level_t maxLevel, const std::string& name,
                std::unique_ptr<Writer>&& writer, std::unique_ptr<Formatter>&& formatter) noexcept {
    return add(id, maxLevel, Severity::NONE, name, std::move(writer), std::move(formatter));
}

bool StorageLoggers::remove(id_t id, Severity severity) noexcept {
    return remove(id, severity, std::string{});
}

bool StorageLoggers::remove(id_t id, const std::string& name) noexcept {
    return remove(id, Severity::NONE, name);
}

void StorageLoggers::add(id_t id, level_t maxLevel, Severity severity, const std::string& name,
                         std::unique_ptr<Writer>&& writer, std::unique_ptr<Formatter>&& formatter) noexcept {
    auto& instance = StorageLoggers::instance();
    std::unique_lock lock(instance.mutex_);
    const auto it = instance.storage_.find(id);
    if (it == instance.storage_.end()) {
        std::vector<SettingsLogger> loggers;
        loggers.emplace_back(SettingsLogger{
                SettingsLogger{maxLevel, severity, name,
                               std::move(writer),
                               std::move(formatter)}
        });
        instance.storage_.emplace(id, std::move(loggers));
        return;
    }

    it->second.emplace_back(SettingsLogger{maxLevel, severity, name,
                                           std::move(writer),
                                           std::move(formatter)});
}

bool StorageLoggers::remove(id_t id, Severity severity, const std::string& name) noexcept{
    auto& instance = StorageLoggers::instance();
    std::unique_lock lock(instance.mutex_);
    const auto it = instance.storage_.find(id);
    if (it == instance.storage_.end()) {
        return false;
    }
    if (severity == Severity::ALL || (it->second.size() == 1 &&
        ((it->second.at(0).name == name && !name.empty()) ||
            (it->second.at(0).severity == severity && severity != Severity::NONE)))) {
        instance.storage_.erase(id);
        return true;
    }
    for(auto logger_it = it->second.begin(); logger_it != it->second.end(); ++logger_it) {
        if ((it->second.at(0).name == name && !name.empty()) ||
                (it->second.at(0).severity == severity && severity != Severity::NONE)) {
            it->second.erase(logger_it);
            return true;
        }
    }
    return false;
}

bool StorageLoggers::write(const Recorder& recorder) noexcept {
    auto& instance = StorageLoggers::instance();
    std::unique_lock lock(instance.mutex_);
    const auto it = instance.storage_.find(recorder.getLoggerId());
    if (it == instance.storage_.end()) {
        return false;
    }

    auto isWrote = false;
    for (const auto& setting : it->second) {
        if (!isWrite(recorder, setting)) {
            continue;
        }
        const auto str = setting.formatter->fmt(recorder);
        setting.writer->write(str);
        isWrote = true;
    }
    return isWrote;
}

StorageLoggers& StorageLoggers::instance() noexcept {
    static StorageLoggers instance;
    return instance;
}

bool StorageLoggers::isWrite(const Recorder& recorder, const SettingsLogger& settings) noexcept {
    return (settings.severity == Severity::ALL
        || (recorder.getSeverity() <= settings.severity && settings.severity != Severity::NONE)
        || (recorder.getName() == settings.name && !settings.name.empty())
        || recorder.getSeverity() == Severity::ALL)
        && recorder.getLevel() <= settings.maxLevel;
}