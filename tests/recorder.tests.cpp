#include <doctest/doctest.h>
#include <ips/logger/recorder.hpp>
#include <limits>
#include <chrono>
#include <stdexcept>
#include <random>

using namespace ::ips::logger;

class RecorderFixture {
public:
    RecorderFixture() : recorder(severity, level, loggerId) {}

    template<typename T>
    void check_value(const T& value, const std::string& expected) {
        recorder << value;
        CHECK(recorder.getBuffer() == expected);
    }

    template<typename TYPE>
    void check_numeric_value() {
        SUBCASE("min") {
            auto value = std::numeric_limits<TYPE>::min();
            check_value(value, std::to_string(value));
        }
        SUBCASE("max") {
            auto value = std::numeric_limits<TYPE>::max();
            check_value(value, std::to_string(value));
        }
        if constexpr (std::is_integral_v<TYPE>) {
            SUBCASE("random") {
                std::default_random_engine randomEngine{std::random_device{}()};
                std::uniform_int_distribution<TYPE> dist{std::numeric_limits<TYPE>::min(), std::numeric_limits<TYPE>::max()};
                auto value = dist(randomEngine);
                check_value(value, std::to_string(value));
            }
        }
    }

    template<typename TYPE>
    void check_double_value() {
        SUBCASE("min") {
            auto value = static_cast<TYPE>(-42.1);
            check_value(value, "-42.1");
        }
        SUBCASE("max") {
            auto value = static_cast<TYPE>(42.1);
            check_value(value, "42.1");
        }

        SUBCASE("zero") {
            auto value = static_cast<TYPE>(0);
            check_value(value, "0");
        }
    }

    static constexpr Severity severity = Severity::DEBUG;
    static constexpr level_t level = level_t{6};
    static constexpr id_t loggerId = id_t{233};
    Recorder recorder;
};

TEST_SUITE_BEGIN("recorder");

TEST_CASE("correct constructor") {
	auto severity = Severity::DEBUG;
	auto level = level_t{6};
	auto loggerId = id_t{233};

    auto firstTimestamp = std::chrono::system_clock::now().time_since_epoch().count();
	auto rec = Recorder{severity, level, loggerId};
    auto secondTimestamp = std::chrono::system_clock::now().time_since_epoch().count();

	CHECK(rec.getSeverity() == severity);
	CHECK(rec.getLevel() == level);
	CHECK(rec.getLoggerId() == loggerId);
	CHECK(rec.getBuffer().empty());
	CHECK(rec.getTimestamp() >= firstTimestamp);
    CHECK(rec.getTimestamp() <= secondTimestamp);
}

TEST_CASE_FIXTURE(RecorderFixture, "format") {
    SUBCASE("unsigned") {
        check_numeric_value<unsigned>();
    }

    SUBCASE("unsigned long") {
        check_numeric_value<unsigned long>();
    }

    SUBCASE("unsigned long long") {
        check_numeric_value<unsigned long long>();
    }

    SUBCASE("int") {
        check_numeric_value<int>();
    }

    SUBCASE("long") {
        check_numeric_value<long>();
    }

    SUBCASE("long long") {
        check_numeric_value<long long>();
    }

    SUBCASE("double") {
        check_double_value<double>();
    }

    SUBCASE("long double") {
        check_double_value<long double>();
    }

    SUBCASE("float") {
        check_double_value<float>();
    }

    SUBCASE("char") {
        SUBCASE("min") {
            auto value = std::numeric_limits<char>::min();
            check_value(value, std::string{value});
        }
        SUBCASE("max") {
            auto value = std::numeric_limits<char>::max();
            check_value(value, std::string{value});
        }
    }

    SUBCASE("bool") {
        SUBCASE("true") {
            check_value(true, "true");
        }
        SUBCASE("false") {
            check_value(false, "false");
        }
    }

    SUBCASE("exception") {
        try {
            throw std::runtime_error("runtime error");
        } catch (std::exception& e) {
            recorder << e;
        }
        CHECK(recorder.getBuffer() == "runtime error");
    }

    SUBCASE("string") {
        auto value = std::string{"foo"};
        check_value(value, value);
    }

    SUBCASE("string_view") {
        auto value = std::string_view{"baz"};
        recorder << value;
        CHECK(recorder.getBuffer() == value);
    }
}

TEST_SUITE_END();