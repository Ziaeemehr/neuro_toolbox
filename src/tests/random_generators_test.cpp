#define CATCH_CONFIG_MAIN
#include "neuro_toolbox.hpp"
#include "catch.hpp"

TEST_CASE("test timing", " ")
{
    const int seed = 1245;
    const int low = 0;
    const int high = 5;
    const int size = 3;
    auto r = NTB::randint(low, high, size, seed);
    // for (auto i : r)
    //     std::cout << i << "\n";


    REQUIRE(r[0] == 0);
}

