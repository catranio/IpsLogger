#include <doctest/doctest.h>
#include <ips/logger/recorder.hpp>

TEST_CASE("get value correct") {
	auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
	int value = 1;
	rec << value;
	REQUIRE(rec.getBuffer() == "1");
}


TEST_CASE("get value correct") {
	SUBCASE("get int") {
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		int value = 1;
		rec << value;
		CHECK(rec.getBuffer() == "1");
	}

	SUBCASE("get unsigned int") {
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		unsigned value = 1;
		rec << value;
		CHECK(rec.getBuffer() == "1");
	}

	SUBCASE("get double") {
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		double value = 1.1;
		rec << value;
		CHECK(rec.getBuffer() == "1.1");
	}

	SUBCASE("get float") {
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		float value = 1.1f;
		rec << value;
		CHECK(rec.getBuffer() == "1.1");
	}

	SUBCASE("get char") {
	auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		char value = 'a';
		rec << value;
		CHECK(rec.getBuffer() == "a");
	}

	SUBCASE("get exception") {
		auto rec = ips::logger::Recorder{ips::logger::Severity::ALL, 3, 0};
		try {
			throw std::runtime_error("runtime error");
		} catch (std::exception& e) {
			rec << e.what();
		}
		CHECK(rec.getBuffer() == "runtime error");
	}
}
