#include <catch2/catch_test_macros.hpp>
#include <ips/logger/recorder.hpp>

TEST_CASE("get value correct", "[recorder]") {
	SECTION("get int") {
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		int value = 1;
		rec << value;
		REQUIRE(rec.getBuffer() == "1");
	}

	SECTION("get unsigned int") {
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		unsigned value = 1;
		rec << value;
		REQUIRE(rec.getBuffer() == "1");
	}

	SECTION("get double") {
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		double value = 1.1;
		rec << value;
		REQUIRE(rec.getBuffer() == "1.1");
	}

	SECTION("get float") {
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		float value = 1.1f;
		rec << value;
		REQUIRE(rec.getBuffer() == "1.1");
	}

	SECTION("get char") {
	auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		char value = 'a';
		rec << value;
		REQUIRE(rec.getBuffer() == "a");
	}

	SECTION("get exception") {
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		try {
			throw std::runtime_error("runtime error");
		} catch (std::exception& e) {
			rec << e.what();
		}
		REQUIRE(rec.getBuffer() == "runtime error");
	}
}
