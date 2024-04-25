#ifndef IPSLOGGER_DETAILS_CONSOLEFROMATTER_HPP
#define IPSLOGGER_DETAILS_CONSOLEFROMATTER_HPP

#include "dateFormatter.hpp"

namespace ips::logger::details {
class ConsoleFormatter final : public DateFormatter {
 public:
  void fmt(const Recorder& recorder, std::string& dest) const noexcept override;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_CONSOLEFROMATTER_HPP */
