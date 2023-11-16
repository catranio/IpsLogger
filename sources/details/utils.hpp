#ifndef IPSLOGGER_DETAILS_UTILS_HPP
#define IPSLOGGER_DETAILS_UTILS_HPP

#include <chrono>
#include <string>

namespace ips::logger::details::utils {
std::string to_string(const std::chrono::system_clock::time_point tp) noexcept;
}  // namespace ips::logger::details::utils

#endif /* IPSLOGGER_DETAILS_UTILS_HPP */
