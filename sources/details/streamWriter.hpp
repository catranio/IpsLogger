#ifndef IPSLOGGER_DETAILS_STREAMWRITER_HPP
#define IPSLOGGER_DETAILS_STREAMWRITER_HPP

#include <iosfwd>
#include <ips/logger/writer.hpp>

namespace ips::logger::details {
class StreamWriter : public Writer {
 public:
  explicit StreamWriter(std::ostream& os);
  ~StreamWriter() override;

  void write(std::string_view data) noexcept final;

 private:
  std::ostream& os_;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_STREAMWRITER_HPP */
