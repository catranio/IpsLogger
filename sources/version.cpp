#include <ips/logger/version.hpp>
#include <fmt/format.h>

const unsigned ips::logger::Version::major = 0;
const unsigned ips::logger::Version::minor = 0;
const unsigned ips::logger::Version::patch = 0;

const std::string ips::logger::Version::version_ = fmt::format(FMT_STRING("{}.{}.{}"), major, minor, patch);

[[maybe_unused]]
std::string ips::logger::Version::pretty() noexcept {
	return fmt::format(FMT_STRING("IpsLogger version: {}"), version_);
}

[[maybe_unused]]
std::string_view ips::logger::Version::version() noexcept {
	return version_;
}
