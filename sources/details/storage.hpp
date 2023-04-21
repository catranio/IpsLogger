#ifndef IPSLOGGER_DETAILS_STORAGE_HPP
#define IPSLOGGER_DETAILS_STORAGE_HPP

#include "logger.hpp"
#include <ips/logger/recorder.hpp>

#include <string_view>
#include <unordered_map>
#include <vector>

namespace ips::logger::details {
	class Storage final {
	private:
		Storage() = default;
		~Storage() = default;
	public:
		Storage(const Storage&) = delete;
		Storage(Storage&&) = delete;
		Storage& operator=(const Storage&) = delete;
		Storage&& operator=(Storage&&) = delete;

	public:
		static Storage& instance() noexcept;
		void add(Logger&& logger) noexcept;
		void remove(const id_t& id) noexcept;
		void write(const Recorder& recorder) noexcept;

	private:
		static bool isWrite(const Recorder& recorder, const Logger& logger) noexcept;

	private:
		using storage_t = std::unordered_map<std::string, Logger>;
		storage_t storage_;
	};
}

#endif /* IPSLOGGER_DETAILS_STORAGE_HPP */
