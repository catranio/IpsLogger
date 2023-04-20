#include "storage.hpp"

using namespace ips::logger::details;

Storage& Storage::instance() noexcept {
	static Storage storage;
	return storage;
}

void Storage::add(Logger&& logger) noexcept {
	const auto& key = logger.getName();
	auto it = storage_.find(std::string{key});
	if (it == storage_.end()) {
		storage_.emplace(key, std::move(logger));
		return;
	}
	it->second = std::move(logger);
}

void Storage::write(const Recorder& recorder) noexcept {
	const auto& id = recorder.getId();
	auto it = storage_.find(id);
	if (it == storage_.end()) {
		return;
	}

	const auto& logger = it->second;
	const auto& msg = logger.getFormatter()->fmt(recorder);
	logger.getWriter()->write(msg);
}