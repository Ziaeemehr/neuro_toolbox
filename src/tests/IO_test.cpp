#define CATCH_CONFIG_MAIN
#include "neuro_toolbox.hpp"
#include "catch.hpp"
#include <vector>

TEST_CASE("Read single column file", " ")
{
    std::vector<int> vec = Neuro::read_vector<int>("data/single_column_integer.txt");
    REQUIRE(vec[1] == 8);
}

TEST_CASE("Read matrix", " ")
{
    std::vector<std::vector<int>> A = Neuro::read_matrix<int>(
        "data/matrix_integer.txt",
        4,
        3);
    REQUIRE(A[0][0] == 1);
    REQUIRE(A[1][0] == -4);
}


// Compile & run:
// - g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -o prog prog.cpp && ./prog --success
