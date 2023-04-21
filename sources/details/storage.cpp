#include "storage.hpp"

using namespace ips::logger::details;

Storage& Storage::instance() noexcept {
	static Storage storage;
	return storage;
}

void Storage::add(Logger&& logger) noexcept {
	const auto& key = logger.getId();
	auto it = storage_.find(std::string{key});
	if (it == storage_.end()) {
		storage_.emplace(key, std::move(logger));
		return;
	}
	assert(it == storage_.end() "ipslogger already register by id=" + key);
}

void Storage::remove(const id_t& id) noexcept {
	auto it = storage_.find(id);
	if (it == storage_.end()) {
		return;
	}
	storage_.erase(it);
}

void Storage::write(const Recorder& recorder) noexcept {
	const auto& id = recorder.getId();
	auto it = storage_.find(id.data());
	if (it == storage_.end() || isWrite(recorder, it->second) ) {
		return;
	}

	const auto& logger = it->second;
	const auto& msg = logger.getFormatter().fmt(recorder);
	logger.getWriter().write(msg);
}

bool Storage::isWrite(const Recorder& recorder, const Logger& logger) noexcept {
	if (recorder.getLevel() > logger.getMaxLevel()) {
		return false;
	}

	if (logger.getSeverityEqualMode() == Logger::SeverityEqualMode::STRONG) {
		return recorder.getSeverity() == logger.getSeverity();
	}

	return recorder.getSeverity() <= logger.getSeverity();
}