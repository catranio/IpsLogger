#include "fileWriter.hpp"

#include <fmt/chrono.h>

#include <filesystem>
#include <thread>

namespace ips::logger::details {

FileWriter::FileWriter(const std::string_view filename,
                       const std::chrono::seconds intervalRotate)
    : filename_(filename), intervalRotate_(intervalRotate) {
  open(filename_);
  if (intervalRotate_ > std::chrono::seconds{1}) {
    rotate();
  }
}

FileWriter::~FileWriter() { file_.close(); }

void FileWriter::write([[maybe_unused]] const std::string_view data) noexcept {
  file_.write(data.data(), static_cast<long>(data.size()));
}

void FileWriter::rotate() noexcept {
  std::thread t([this] {
    while (true) {
      if (intervalRotate_ < std::chrono::seconds{1}) return;
      std::this_thread::yield();
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

bool FileWriter::open(const std::string_view filename) noexcept {
  file_.open(filename.data(), std::ios::out | std::ios::app);
  return file_.is_open();
}

std::string FileWriter::dataPrefix() const noexcept {
  using namespace std::chrono_literals;
  const auto now = std::chrono::system_clock::now();
  if (intervalRotate_ < 60s) {
    return fmt::format("_{:%Y%m%d_%H%M%S}", now);
  }
  if (intervalRotate_ < 1h) {
    return fmt::format("_{:%Y%m%d_%H%M}", now);
  }
  if (intervalRotate_ < 24h) {
    return fmt::format("_{:%Y%m%d_%H}", now);
  }
  return fmt::format("_{:%Y%m%d}", now);
}

}  // namespace ips::logger::details
