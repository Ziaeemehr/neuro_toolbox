/*! 
 * \author Abolfazl Ziaeemehr
 * \version 0.1
 * \date Nov. 2020
 * \mainpage IO for input/output data 
*/

#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h> /* exit, EXIT_FAILURE */

namespace Neuro
{

    template <typename T>
    inline std::vector<T> read_vector(std::string filename)
    {
        /*!
        * Read numbers from single column text file
        * 
        * \param filename [std::string] input file name
        * \return a vector of numbers of type specified 
        * 
        * **example:** 
        * 
        * std::vector<double> vec = read_from_file<double>("my_file.txt"); 
        */

        std::vector<T> numbers;
        std::ifstream inputFile(filename);
        if (inputFile.good())
        {
            T current_number = 0;
            while (inputFile >> current_number)
                numbers.push_back(current_number);

            inputFile.close();
        }

        else /*! exit if it does not found the input file */
        {
            std::cout << "Error reading " << filename << "\n";
            exit(EXIT_FAILURE);
        }

        return numbers;
    }
    //-------------------------------------------------------------------------
    inline bool fileExists(const std::string &filename)
    {
        /*!
        check whether file with given name exist

        * \param filename [string] input file name
        * \return true if input file exists
        */

        struct stat buf;
        if (stat(filename.c_str(), &buf) != -1)
        {
            return true;
        }
        return false;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    inline std::vector<std::vector<T>> read_matrix(
        const std::string filename,
        const int row,
        const int col)
    {
        /*!
        * Read matrix into vector of vector
        * 
        * \param filename [string] name of text file to read
        * \param row [int] number of rows
        * \param col [int] number of columns
        
        * \return vector of vector of specified type
        *
        * **example** 
        * std::vector<std::vector<int>> A = Neuro::read_matrix<int>(
        * "data/matrix_integer.txt", 4, 3);
        */

        std::ifstream ifile(filename);

        /*to check if input file exists*/
        if (fileExists(filename))
        {
            std::vector<std::vector<T>> Cij(row, std::vector<T>(col));

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    ifile >> Cij[i][j];
                }
            }
            ifile.close();
            return Cij;
        }
        else
        {
            std::cerr << "\n file : " << filename << " not found \n";
            exit(2);
        }
    }

    //-------------------------------------------------------------------------

} // namespace Neuro

#endif // !IO_HPP