#ifndef IPSLOGGER_DETAILS_FILEWRITER_HPP
#define IPSLOGGER_DETAILS_FILEWRITER_HPP

#include <chrono>
#include <fstream>
#include <ips/logger/writer.hpp>
#include <string>

namespace ips::logger::details {
class FileWriter final : public Writer {
 public:
  explicit FileWriter(std::string_view filename,
                      std::chrono::seconds intervalRotate = {});

  ~FileWriter() override;

  void write(std::string_view data) noexcept override;

 private:
  void rotate() noexcept;
  bool open(std::string_view filename) noexcept;
  std::string dataPrefix() const noexcept;

  std::ofstream file_;
  std::string filename_;
  std::chrono::seconds intervalRotate_;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_FILEWRITER_HPP */
