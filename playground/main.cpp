#include <algorithm>
#include <ips/logger/log.hpp>
#include <random>
#include <ranges>

int main() {
  std::mt19937_64 gen{std::random_device{}()};
  std::uniform_int_distribution<unsigned> dist{
      1, static_cast<unsigned>(ips::logger::Severity::kDebug)};

  ipslog::init::console(ips::logger::Severity::kAll);
  // std::ranges::for_each(
  //     std::views::iota(1u, 120u), [&dist, &gen](const auto idx) noexcept {
  //       const auto sev = static_cast<ips::logger::Severity>(dist(gen));
  //       ipslog::log(sev, 4)
  //           << "This specialization of std::ranges::enable_borrowed_range "
  //              "makes iota_view satisfy borrowed_range."
  //           << idx;
  //     });
  return 0;
}