#ifndef IPSLOGGER_TIME_CONVERTION_HPP
#define IPSLOGGER_TIME_CONVERTION_HPP

#include <benchmark/benchmark.h>
#include <date/date.h>
namespace logger::details {
[[maybe_unused]] static void hmdataTimePointToSeconds(benchmark::State& state) {
  const auto tp = std::chrono::system_clock::now();
  for ([[maybe_unused]] auto _ : state) {
    const auto tpl = date::local_days{} + (tp - std::chrono::sys_days{});
    const auto tpd = std::chrono::floor<std::chrono::days>(tpl);
    const auto ymd [[maybe_unused]] = date::year_month_day{tpd};
    const auto hms = date::hh_mm_ss{tpl - tpd};
    [[maybe_unused]] const auto seconds = hms.seconds();
  }
}

[[maybe_unused]] static void chronoTimePointToSeconds(benchmark::State& state) {
  const auto tp = std::chrono::system_clock::now();
  for ([[maybe_unused]] auto _ : state) {
    [[maybe_unused]] const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
  }
}

std::string to_string(std::chrono::system_clock::time_point tp) {
    const auto tpl = date::local_days{} + (tp - std::chrono::sys_days{});
    const auto tpd = std::chrono::floor<std::chrono::days>(tpl);
    const auto ymd [[maybe_unused]] = date::year_month_day{tpd};
    const auto hms = date::hh_mm_ss{tpl - tpd};
    constexpr auto kFractionalWidth = decltype(hms)::fractional_width;
    std::string buffer(20 + kFractionalWidth, '0');
    [[ maybe_unused]] auto* const ptr = buffer.data();
    auto assignChars = [&buffer](const auto shift, std::integral auto x) {
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
    assignChars(4, int{ymd.year()});
    assignChars(7, unsigned{ymd.month()});
    assignChars(10, unsigned{ymd.day()});
    assignChars(13, hms.hours().count());
    assignChars(16, hms.minutes().count());
    assignChars(19, hms.seconds().count());
    assignChars(20 + kFractionalWidth, hms.subseconds().count());
    return buffer;
}


std::string to_string_tail(const std::chrono::system_clock::time_point tp) noexcept {
  const auto tpl = date::local_days{} + (tp - std::chrono::sys_days{});
  const auto tpd = std::chrono::floor<std::chrono::days>(tpl);
  const auto ymd [[maybe_unused]] = date::year_month_day{tpd};
  const auto hms = date::hh_mm_ss{tpl - tpd};
  constexpr auto kFractionalWidth = decltype(hms)::fractional_width;
  std::string buffer(kFractionalWidth, '0');
  auto toChars = [&buffer](const auto shift, std::integral auto x) {
    auto* p = buffer.data() + shift;
    do {
      *--p = static_cast<char>(x % 10 + '0');
      x /= 10;
    } while (x != 0);
  };
  toChars(kFractionalWidth, hms.subseconds().count());
  return buffer;
}

std::string to_string_chache(const std::chrono::system_clock::time_point tp) noexcept {
  static std::chrono::seconds lastLoggedSeconds = {};
  static std::string chachedTimestamp;
  const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch());
  if (seconds == lastLoggedSeconds) {
    std::string res;
    res.reserve(26);
    res.assign(chachedTimestamp);
    res.append(".");
    res.append(to_string_tail(tp));
    return res;
  }
  lastLoggedSeconds = seconds;
  const auto timestamp = to_string(tp);
  chachedTimestamp = timestamp.substr(0, 19);
  return chachedTimestamp;
}

[[maybe_unused]] static void timepointToSting(benchmark::State& state) {
  const auto tp = std::chrono::system_clock::now();
  for ([[maybe_unused]] auto _ : state) {
   [[maybe_unused]] const auto res = to_string(tp);
  }
}

[[maybe_unused]] static void timepointToStingChahed(benchmark::State& state) {
  const auto tp = std::chrono::system_clock::now();
  for ([[maybe_unused]] auto _ : state) {
    [[maybe_unused]] const auto res = to_string_chache(tp);
  }
}

}  // namespace logger::details

#endif /* IPSLOGGER_TIME_CONVERTION_HPP */
