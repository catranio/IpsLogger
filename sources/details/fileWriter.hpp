#ifndef IPSLOGGER_DETAILS_FILEWRITER_HPP
#define IPSLOGGER_DETAILS_FILEWRITER_HPP

#include <chrono>
#include <fstream>
#include <ips/logger/writer.hpp>
#include <string>

namespace ips::logger::details {
class FileWriter : public Writer {
 public:
  explicit FileWriter(std::string_view filename,
                      std::chrono::seconds intervalRotate = {});

  ~FileWriter() override;

  void write(std::string_view data) noexcept final;

 private:
  void rotate() noexcept;
  bool open(std::string_view filename) noexcept;
  std::string dataPrefix() const noexcept;

 private:
  using seconds_t = std::chrono::seconds;
  std::ofstream file_;
  std::string filename_;
  seconds_t intervalRotate_;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_FILEWRITER_HPP */
