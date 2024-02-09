#ifndef IPSLOGGER_DETAILS_CONSOLEFROMATTER_HPP
#define IPSLOGGER_DETAILS_CONSOLEFROMATTER_HPP

#include "dateFormatter.hpp"

namespace ips::logger::details {
class ConsoleFormatter : public DateFormatter {
 public:
  void fmt(const Recorder& recorder, std::string& dest) const noexcept final;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_CONSOLEFROMATTER_HPP */
