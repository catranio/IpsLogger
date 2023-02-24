#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

int main() {
	doctest::Context context;
	context.setOption("no-intro", true);
	context.setOption("no-version", true);
	auto test_result = context.run();
	return test_result;
}