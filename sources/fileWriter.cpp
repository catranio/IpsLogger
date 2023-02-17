#include <ips/logger/ditails/fileWriter.hpp>

using namespace ips::logger::ditails;

FileWriter::FileWriter(std::string_view filename) {
    file_.open(filename.data(), std::ios::binary | std::ios::out);
    if (file_.is_open()) {
        //todo: write what to do
    }
}

void FileWriter::write(std::string_view data) noexcept {
    //todo: rewrite without flush
    file_ << data;
    file_.flush();
}

FileWriter::~FileWriter() {
    file_.close();
}