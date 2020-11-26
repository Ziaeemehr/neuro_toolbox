#define CATCH_CONFIG_MAIN
#include "neuro_toolbox.hpp"
#include "catch.hpp"

#include <iostream>
#include <chrono>
#include <thread>

TEST_CASE("test timing", " ")
{
    double start = Neuro::get_wall_time();
    double end = Neuro::get_wall_time();
    Neuro::display_timing(end - start, 0);

    REQUIRE(1 == 1);
}
