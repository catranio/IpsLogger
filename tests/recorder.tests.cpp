#include <doctest/doctest.h>

#include <chrono>
#include <ips/logger/log.hpp>
#include <ips/logger/recorder.hpp>
#include <limits>
#include <random>
#include <stdexcept>

class RecorderFixture {
 public:
  RecorderFixture() = default;

  template <typename T>
  void check_value(const T& value, const std::string_view expected) {
    recorder_ << value;
    CHECK(recorder_.getBuffer() == expected);
  }

  template <typename TYPE>
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
        std::uniform_int_distribution<TYPE> dist{
            std::numeric_limits<TYPE>::min(), std::numeric_limits<TYPE>::max()};
        auto value = dist(randomEngine);
        check_value(value, std::to_string(value));
      }
    }
  }

  template <typename TYPE>
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

  ips::logger::Recorder& getRecorder() { return recorder_; }

 private:
  static constexpr ips::logger::Severity kSeverity =
      ips::logger::Severity::kDebug;
  static constexpr ips::logger::level_t kLevel = ips::logger::level_t{6};
  ips::logger::Recorder recorder_ = {"", kSeverity, kLevel};
};

TEST_SUITE_BEGIN("recorder");

TEST_CASE("correct constructor severity") {
  using namespace ips::logger;
  auto severity = Severity::kDebug;
  auto level = level_t{6};

  auto firstTimestamp = std::chrono::system_clock::now();
  auto rec = Recorder{"", severity, level};
  auto secondTimestamp = std::chrono::system_clock::now();

  CHECK(rec.getSeverity() == severity);
  CHECK(rec.getId() == std::string{});
  CHECK(rec.getLevel() == level);
  CHECK(rec.getBuffer().empty());
  CHECK(rec.getTimestamp() >= firstTimestamp);
  CHECK(rec.getTimestamp() <= secondTimestamp);
}

TEST_CASE("correct constructor name") {
  using namespace ips::logger;
  auto id = std::string{"alarm.cdr"};
  auto level = level_t{6};

  auto firstTimestamp = std::chrono::system_clock::now();
  auto rec = Recorder{id, Severity::kTrace, level};
  auto secondTimestamp = std::chrono::system_clock::now();

  CHECK(rec.getId() == id);
  CHECK(rec.getSeverity() == Severity::kTrace);
  CHECK(rec.getLevel() == level);
  CHECK(rec.getBuffer().empty());
  CHECK(rec.getTimestamp() >= firstTimestamp);
  CHECK(rec.getTimestamp() <= secondTimestamp);
}

TEST_SUITE_END();

TEST_CASE_FIXTURE(RecorderFixture, "format") {
  SUBCASE("unsigned") { check_numeric_value<unsigned>(); }

  SUBCASE("unsigned long") { check_numeric_value<unsigned long>(); }

  SUBCASE("unsigned long long") { check_numeric_value<unsigned long long>(); }

  SUBCASE("int") { check_numeric_value<int>(); }

  SUBCASE("long") { check_numeric_value<long>(); }

  SUBCASE("long long") { check_numeric_value<long long>(); }

  SUBCASE("double") { check_double_value<double>(); }

  SUBCASE("long double") { check_double_value<long double>(); }

  SUBCASE("float") { check_double_value<float>(); }

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
    SUBCASE("true") { check_value(true, "true"); }
    SUBCASE("false") { check_value(false, "false"); }
  }

  SUBCASE("exception") {
    getRecorder() << std::runtime_error{"runtime error"};
    CHECK(getRecorder().getBuffer() == "runtime error");
  }

  SUBCASE("string") {
    auto value = std::string{"foo"};
    check_value(value, value);
  }

  SUBCASE("string_view") {
    auto value = std::string_view{"baz"};
    getRecorder() << value;
    CHECK(getRecorder().getBuffer() == value);
  }

  SUBCASE("fmt_format") {
    auto value = 42;
    getRecorder()("fmt: {}", value);
    CHECK(getRecorder().getBuffer() == "fmt: 42");
  }
}

TEST_SUITE_END();

TEST_SUITE_BEGIN("custom record functions");

ipslog_gen_funcs(ips);

TEST_CASE("fatal") { ips::logger::ips_fatal() << "ips.fatal: " << 1; }
TEST_CASE("error") { ips::logger::ips_error() << "ips.error: " << 1; }
TEST_CASE("warning") { ips::logger::ips_warning() << "ips.warning: " << 1; }
TEST_CASE("info") { ips::logger::ips_info() << "cpe.info: " << 1; }
TEST_CASE("trace") { ips::logger::ips_trace() << "cpe.trace: " << 1; }
TEST_CASE("debug") { ips::logger::ips_debug() << "cpe.debug: " << 1; }

TEST_SUITE_END();

TEST_SUITE_BEGIN("version");

TEST_CASE_FIXTURE(RecorderFixture, "version") {
  using namespace ips::logger;
  const auto value = Version::version();
  getRecorder() << value;
  CHECK(getRecorder().getBuffer() == value);
}

TEST_CASE_FIXTURE(RecorderFixture, "version pretty") {
  using namespace ips::logger;
  const auto value = Version::pretty();
  getRecorder() << value;
  CHECK(getRecorder().getBuffer() == value);
}

TEST_SUITE_END();
