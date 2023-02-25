#include <doctest/doctest.h>
#include <ips/logger/recorder.hpp>
#include <limits>
#include <sstream>

TEST_CASE("correct constructor") {
	auto severity = ips::logger::Severity::DEBUG;
	auto level = ips::logger::level_t{6};
	auto loggerId = ips::logger::id_t{233};

	auto rec = ips::logger::Recorder{severity, level, loggerId};

	CHECK(rec.getSeverity() == severity);
	CHECK(rec.getLevel() == level);
	CHECK(rec.getLoggerId() == loggerId);
	CHECK(rec.getBuffer().empty());
}

template<typename T>
void check_value(const T& value, const std::string& expected) {
	auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
	rec << value;
	CHECK(rec.getBuffer() == expected);
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
			auto value = std::numeric_limits<TYPE>::max() % static_cast<TYPE>(rand());
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

TEST_CASE("") {
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
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		try {
			throw std::runtime_error("runtime error");
		} catch (std::exception& e) {
			rec << e.what();
		}
		CHECK(rec.getBuffer() == "runtime error");
	}
}
