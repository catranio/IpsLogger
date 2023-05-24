#include <doctest/doctest.h>
#include <ips/logger/recorder.hpp>

class CustomObject {
public:
    [[nodiscard]] std::string toString() const {
        return "CustomObject to_string work!";
    }

    friend ::ips::logger::Recorder &
    operator<<(::ips::logger::Recorder &recorder, const CustomObject &customObject) noexcept {
        recorder << customObject.toString();
        return recorder;
    }
};

using namespace ips::logger;

TEST_SUITE_BEGIN("custom recorder 'operator <<'");

TEST_CASE("equal buffer") {
    CustomObject customObject;
    Recorder rec{"", Severity::ALL, 4};
    rec << customObject;
    CHECK(rec.getBuffer() == customObject.toString());
}

TEST_SUITE_END();