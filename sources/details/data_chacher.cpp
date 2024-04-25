#include "data_chacher.hpp"
#include "utils.hpp"
#include <chrono>

namespace ips::logger::details::utils
{
std::string DataChacher::to_string(const std::chrono::system_clock::time_point tp) noexcept {
  const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
  if (seconds == lastLoggedSeconds_) {
    return chachedTimestamp_ + "." + to_string_tail(tp);
  }
  lastLoggedSeconds_ = seconds;
  const auto timestamp = utils::to_string(tp);
  chachedTimestamp_ = timestamp.substr(0, 19);
  return timestamp;
}
} // ips::logger::details::utils
