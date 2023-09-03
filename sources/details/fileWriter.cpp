#include "fileWriter.hpp"

#include <fmt/chrono.h>

#include <filesystem>
#include <thread>

namespace ips::logger::details {

FileWriter::FileWriter(std::string_view filename,
                       std::chrono::seconds intervalRotate)
    : filename_(filename), intervalRotate_(intervalRotate) {
  open(filename_);
  using namespace std::chrono;
  if (intervalRotate_ > seconds{1}) {
    rotate();
  }
}

FileWriter::~FileWriter() { file_.close(); }

void FileWriter::write(std::string_view data) noexcept {
  file_.write(data.data(), static_cast<long>(data.size()));
}

void FileWriter::rotate() noexcept {
  std::thread t([this]() {
    while (true) {
      if (intervalRotate_ < std::chrono::seconds{1}) return;
      std::this_thread::sleep_for(std::chrono::seconds(intervalRotate_));
      if (intervalRotate_ < std::chrono::seconds{1}) return;
      auto fs = std::filesystem::path{filename_};
      auto filename =
          fs.stem().string() + "_" + dataPrefix() + fs.extension().string();
      if (file_.is_open()) file_.close();
      open(filename);
    }
  });
  t.detach();
}

bool FileWriter::open(std::string_view filename) noexcept {
  file_.open(filename.data(), std::ios::out | std::ios::app);
  return file_.is_open();
}

std::string FileWriter::dataPrefix() const noexcept {
  using namespace std::chrono;
  const auto now = system_clock::now();
  if (intervalRotate_ < seconds{60}) {
    return fmt::format("_{:%Y%m%d_%H%M%S}", now);
  } else if (intervalRotate_ < hours{1}) {
    return fmt::format("_{:%Y%m%d_%H%M}", now);
  } else if (intervalRotate_ < days{1}) {
    return fmt::format("_{:%Y%m%d_%H}", now);
  } else {
    return fmt::format("_{:%Y%m%d}", now);
  }
}

}  // namespace ips::logger::details
