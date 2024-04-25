#ifndef IPSLOGGER_DETAILS_STREAMWRITER_HPP
#define IPSLOGGER_DETAILS_STREAMWRITER_HPP

#include <iosfwd>
#include <ips/logger/writer.hpp>

namespace ips::logger::details {
class StreamWriter final : public Writer {
 public:
  explicit StreamWriter(std::ostream& os);

  void write(std::string_view data) noexcept override;

 private:
  std::ostream& os_;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_STREAMWRITER_HPP */
