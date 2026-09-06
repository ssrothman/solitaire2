#include <catch2/catch_test_macros.hpp>

#include <solitaire2/version.hpp>

TEST_CASE("the backend exposes a scaffold version") {
    REQUIRE(solitaire2::version == "0.1.0");
}
