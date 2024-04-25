#include "utils.hpp"

#include <date/date.h>

std::string ips::logger::details::utils::to_string(
    const std::chrono::system_clock::time_point tp) noexcept {
  const auto tpl = date::local_days{} + (tp - std::chrono::sys_days{});
  const auto tpd = std::chrono::floor<std::chrono::days>(tpl);
  const auto ymd [[maybe_unused]] = date::year_month_day{tpd};
  const auto hms = date::hh_mm_ss{tpl - tpd};
  constexpr auto kFractionalWidth = decltype(hms)::fractional_width;
  std::string buffer(20 + kFractionalWidth, '0');
  auto* const ptr = buffer.data();
  auto toChars = [&buffer](const auto shift, std::integral auto x) {
    auto* p = buffer.data() + shift;
    do {
      *--p = static_cast<char>(x % 10 + '0');
      x /= 10;
    } while (x != 0);
  };
  *(ptr + 4) = *(ptr + 7) = *(ptr + 10) = *(ptr + 19) = '.';
  *(ptr + 13) = *(ptr + 16) = ':';
  *(ptr + 10) = ' ';
  *(ptr + 20 + kFractionalWidth) = 0;
  toChars(4, int{ymd.year()});
  toChars(7, unsigned{ymd.month()});
  toChars(10, unsigned{ymd.day()});
  toChars(13, hms.hours().count());
  toChars(16, hms.minutes().count());
  toChars(19, hms.seconds().count());
  toChars(20 + kFractionalWidth, hms.subseconds().count());
  return buffer;
}
