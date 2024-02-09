#ifndef IPSLOGGER_FORMATTER_HPP
#define IPSLOGGER_FORMATTER_HPP

#include <iosfwd>

namespace ips::logger {
class Recorder;

class Formatter {
 public:
  virtual ~Formatter() = default;

  virtual void fmt(const Recorder& recorder,
                   std::string& dest) const noexcept = 0;
};
}  // namespace ips::logger

#endif /* IPSLOGGER_FORMATTER_HPP */
