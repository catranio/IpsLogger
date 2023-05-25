#ifndef IPSLOGGER_VERSION_HPP
#define IPSLOGGER_VERSION_HPP

#include <iosfwd>
#include <string>

namespace ips::logger {
class Version final {
 public:
  [[maybe_unused]] static std::string pretty() noexcept;
  [[maybe_unused]] static std::string_view version() noexcept;

 public:
  static const unsigned major;
  static const unsigned minor;
  static const unsigned patch;

 private:
  static const std::string version_;
};
}  // namespace ips::logger

#endif /* IPSLOGGER_VERSION_HPP */
