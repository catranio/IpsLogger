#include <doctest/doctest.h>

#include <ips/logger/recorder.hpp>

class CustomObject {
 public:
  [[nodiscard]] std::string toString() const {
    return name_ + " to_string work!";
  }

  friend ::ips::logger::Recorder& operator<<(
      ::ips::logger::Recorder& recorder,
      const CustomObject& customObject) noexcept {
    recorder << customObject.toString();
    return recorder;
  }

 private:
  const std::string name_ = "CustomObject";
};

using namespace ips::logger;

TEST_SUITE_BEGIN("custom recorder 'operator <<'");

TEST_CASE("equal buffer") {
  const CustomObject customObject;
  Recorder rec{"", Severity::kAll, 4};
  rec << customObject;

  CHECK(rec.getBuffer() == customObject.toString());
}

TEST_CASE("equal buffer with prefix") {
  const CustomObject customObject;
  Recorder rec{"", Severity::kAll, 4};
  rec << "one " << customObject;

  CHECK(rec.getBuffer() == "one " + customObject.toString());
}

TEST_SUITE_END();