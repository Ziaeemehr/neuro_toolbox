#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h> /* exit, EXIT_FAILURE */

namespace NTB
{

    template <typename T>
    inline std::vector<T> load_vector(std::string filename)
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
    inline bool file_exists(const std::string &filename)
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
    inline std::vector<std::vector<T>> load_matrix(
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
        if (file_exists(filename))
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
    template <typename T>
    std::vector<std::vector<T>> adjmat_to_adjlist(
        const std::vector<std::vector<T>> &A,
        const double threshold = 1e-8,
        std::string in_degree = "row")
    {
        /*!
        return adjacency list of given adjacency matrix
        * \param A  input adjacency matrix
        * \param threshold  threshold for binarizing 
        * \param in_degree  "row" or "col" to consider input edges on row or col, respectively
        * \return adjacency list as a vector of vector
        * 
        * 
        * **example**
        * adjmat_to_adjlist<int>(A);
        */
        int row = A.size();
        int col = A[0].size();
        std::vector<std::vector<int>> adjlist;

        if (in_degree == "row")
        {
            adjlist.resize(row);

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    if (std::abs(A[i][j]) > 1.e-8)
                        adjlist[i].push_back(j);
                }
            }
        }
        else
        {
            adjlist.resize(col);

            for (int i = 0; i < col; i++)
            {
                for (int j = 0; j < row; j++)
                {
                    if (std::abs(A[i][j]) > 1.e-8)
                        adjlist[i].push_back(j);
                }
            }
        }

        return adjlist;
    }

    //-------------------------------------------------------------------------
    template <typename T>
    void write_matrix_to_file(const std::vector<std::vector<T>> &A,
                              const std::string filename)
    {
        /*! 
        * Write matrix to text file
        
        * \param A input vector of vector of type T.
        * \param filename output text file name.
        * 
        */
        int row = A.size();
        int col = A[0].size();

        std::ofstream ofile;
        ofile.open(filename);
        if (ofile.is_open())
        {
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    ofile << A[i][j] << " ";
                }
                ofile << "\n";
            }
            ofile.close();
        }
        else
            std::cout << "Error opening file to write data. \n";
    }

    //-------------------------------------------------------------------------
    template <typename T>
    void write_vector_to_file(const std::vector<T> &v,
                              const std::string filename)
    {
        /*!
        * Write vector to text file
        * 
        * \param v input vector of type T
        * \param filename output text file name.
        * 
        * Exit if it could not open file to write successfully. 

        */
        size_t n = v.size();
        std::ofstream ofile;
        ofile.open(filename);
        if (ofile.is_open())
        {
            for (size_t i = 0; i < n; ++i)
                ofile << v[i] << "\n";
            ofile.close();
        }
        else
        {
            std::cout << "Error opening file to write data. \n";
            exit(EXIT_FAILURE);
        }
    }
    //-------------------------------------------------------------------------

} // namespace Neuro

#endif // !IO_HPP