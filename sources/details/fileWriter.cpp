#include "fileWriter.hpp"

#include <fmt/chrono.h>
#include <filesystem>
#include <thread>

using namespace ips::logger::details;

FileWriter::FileWriter(std::string_view filename, unsigned rotateInterval) :
		file_(),
		filename_(filename),
		intervalRotate_(rotateInterval) {
	open(filename_);
	if (rotateInterval) {
		rotate();
	}
}

FileWriter::~FileWriter() {
	file_.close();
}

void FileWriter::write(std::string_view data) noexcept {
	file_.write(data.data(), static_cast<long>(data.size()));
}

void FileWriter::rotate() noexcept {
	std::thread t([=]() {
		while (true) {
            if (!intervalRotate_)
                return;
            std::this_thread::sleep_for(std::chrono::seconds(intervalRotate_));
            if (!intervalRotate_)
                return;
            auto fs = std::filesystem::path{filename_};
            auto filename = fs.stem().string() + "_"
                            + fmt::format(rotateFormat(), fmt::localtime(std::time(nullptr)))
                            + fs.extension().string();
            if (file_.is_open())
                file_.close();
            open(filename);
        }
    });
    t.detach();
}

bool FileWriter::open(std::string_view filename) noexcept {
    file_.open(filename.data(), std::ios::out | std::ios::app);
    return file_.is_open();
}

constexpr std::string_view FileWriter::rotateFormat() const noexcept {
    if (intervalRotate_ < 60) {
        return "_{:%Y%m%d_%H%M%S}";
    } else if (intervalRotate_ < 60 * 60) {
        return "_{:%Y%m%d_%H%M}";
    } else if (intervalRotate_ < 60 * 60 * 24) {
        return "_{:%Y%m%d_%H}";
    } else if (intervalRotate_ < 60 * 60 * 24 * 7) {
        return "_{:%Y%m%d}";
    }
    return "{}";
}
