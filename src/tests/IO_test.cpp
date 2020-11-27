#define CATCH_CONFIG_MAIN
#include "neuro_toolbox.hpp"
#include "catch.hpp"
#include <vector>
// #include <string>

TEST_CASE("Read single column file", " ")
{
    std::vector<int> vec = NTB::load_vector<int>("data/single_column_integer.txt");
    REQUIRE(vec[1] == 8);
}

TEST_CASE("Read matrix", " ")
{
    std::vector<std::vector<int>> A = NTB::load_matrix<int>(
        "data/matrix_integer.txt",
        4,
        3);
    REQUIRE(A[0][0] == 1);
    REQUIRE(A[1][0] == -4);
}

TEST_CASE("write matrix to text file", " ")
{
    std::vector<std::vector<int>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
    NTB::write_matrix_to_file<int>(A, "data/write_matrix_to_file.txt");
    std::vector<std::vector<int>> B = NTB::load_matrix<int>(
        "data/write_matrix_to_file.txt",
        4,
        3);
    REQUIRE(A[0][0] == B[0][0]);
    REQUIRE(A[3][2] == B[3][2]);
}

TEST_CASE("write vector to file", " ")
{
    std::vector<int> A{5, 8, 9};
    NTB::write_vector_to_file<int>(A, "data/write_vector_to_file.txt");
    auto B = NTB::load_vector<int>("data/write_vector_to_file.txt");
    REQUIRE(A[1] == B[1]);
}

// Compile & run:
// - g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -o prog prog.cpp && ./prog --success
