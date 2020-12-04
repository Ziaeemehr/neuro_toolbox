#define CATCH_CONFIG_MAIN
#include "neuro_toolbox.hpp"
#include <vector>
// #include <string>

int main(int argc, const char **argv)
{
    {

        /*! 
        Load vector from file (int)
        to load float or double numbers only replace <int> with <float> or <double>
        */
        std::vector<int> vec = NTB::load_vector<int>("data/single_column_integer.txt");

        /*! 
        * Load a matrix from text file
        */
        std::vector<std::vector<int>> A = NTB::load_matrix<int>(
            "data/matrix_integer.txt", // file name
            4,                         // number of rows
            3                          // number of columns
        );
    }

    {
        /*! 
        * Write a matrix to text file
        */
        std::vector<std::vector<int>> A = {{1, 2, 3},
                                           {4, 5, 6},
                                           {7, 8, 9},
                                           {10, 11, 12}};
        NTB::write_matrix_to_file<int>(A, "data/write_matrix_to_file.txt");
    }

    {
        /*!
        * Write a vector to text file
        */
        std::vector<int> A{5, 8, 9};
        NTB::write_vector_to_file<int>(A, "data/write_vector_to_file.txt");
    }

    std::cout << "Done!" << std::endl;

    return 0;
}
