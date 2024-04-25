#ifndef IPS_LOGGER_DATA_CHACHER_HPP
#define IPS_LOGGER_DATA_CHACHER_HPP

#include <chrono>

namespace ips::logger::details::utils
{
  class DataChacher final {
  public:
      [[nodiscard]] std::string to_string(std::chrono::system_clock::time_point tp) noexcept;
  private:
      std::chrono::seconds lastLoggedSeconds_ {};
      std::string chachedTimestamp_;
  };
}

#endif /* IPS_LOGGER_DATA_CHACHER_HPP */
