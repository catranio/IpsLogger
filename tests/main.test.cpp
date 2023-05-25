#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

int main(int argc, char** argv) {
  doctest::Context context{argc, argv};
  context.setOption("no-intro", true);
  context.setOption("no-version", true);
  auto test_result = context.run();
  return test_result;
}
