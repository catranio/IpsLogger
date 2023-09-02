#include <fmt/format.h>

#include <ips/logger/version.hpp>

const unsigned ips::logger::Version::kMajor = 0;
const unsigned ips::logger::Version::kMinor = 0;
const unsigned ips::logger::Version::kPatch = 0;

const std::string ips::logger::Version::kVersion =
    fmt::format(FMT_STRING("{}.{}.{}"), kMajor, kMinor, kPatch);

[[maybe_unused]] std::string ips::logger::Version::pretty() noexcept {
  return fmt::format(FMT_STRING("IpsLogger version: {}"), kVersion);
}

[[maybe_unused]] std::string_view ips::logger::Version::version() noexcept {
  return kVersion;
}
