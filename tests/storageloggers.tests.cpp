#include <doctest/doctest.h>
#include <details/storageLoggers.hpp>

#include <details/fileWriter.hpp>
#include <details/dateFormatter.hpp>
#include <ips/logger/recorder.hpp>
#include <ips/logger/log.hpp>

#include <ranges>

using namespace ::ips::logger;
using namespace ::ips::logger::details;

class StorageLoggersFixture {
public:
    friend StorageLoggers;
};

TEST_SUITE_BEGIN("StorageLoggers");

TEST_CASE_FIXTURE(StorageLoggersFixture, "add") {
    auto writer = std::make_unique<FileWriter>("sss");
    auto formatter = std::make_unique<DateFormatter>();
    auto id = id_t{1};
    StorageLoggers::add(id, 10, Severity::TRACE, std::move(writer), std::move(formatter));

    Recorder rec{Severity::TRACE, 9,  id};
    Recorder rec_info{Severity::INFO, 9,  id};
    Recorder rec_false{Severity::ALL,9,  2};
    CHECK(StorageLoggers::write(rec));
    CHECK(StorageLoggers::write(rec_info));
    CHECK_FALSE(StorageLoggers::write(rec_false));
}

TEST_CASE_FIXTURE(StorageLoggersFixture, "remove") {
    auto writer = std::make_unique<FileWriter>("sss");
    auto formatter = std::make_unique<DateFormatter>();
    for (unsigned i = 0; i < 10; ++i) {
        StorageLoggers::add(id_t{i}, 10, Severity::TRACE, std::move(writer), std::move(formatter));
    }

    for (unsigned i = 0; i < 10; ++i) {
        CHECK_FALSE(StorageLoggers::remove(id_t{i}, Severity::DEBUG));
        CHECK(StorageLoggers::remove(id_t{i}, Severity::TRACE));
    }
}

TEST_SUITE_END();
