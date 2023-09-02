#ifndef IPSLOGGER_VERSION_HPP
#define IPSLOGGER_VERSION_HPP

#include <iosfwd>
#include <string>

namespace ips::logger {
class Version final {
 public:
  [[maybe_unused]] static std::string pretty() noexcept;
  [[maybe_unused]] static std::string_view version() noexcept;

  static const unsigned kMajor;
  static const unsigned kMinor;
  static const unsigned kPatch;

 private:
  static const std::string kVersion;
};
}  // namespace ips::logger

#endif /* IPSLOGGER_VERSION_HPP */
