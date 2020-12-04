#ifndef NEURO_TOOLBOX
#define NEURO_TOOLBOX


// from config.hpp
// ----------------------------------------------------------------------------





// from IO.hpp
// ----------------------------------------------------------------------------

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

// from utility.hpp
// ----------------------------------------------------------------------------

namespace NTB
{
    /*------------------------------------------------------------*/
    double get_wall_time()
    {
        /*! 
        measure real passed time 
        \return wall time in second
        */
        
        struct timeval time;
        if (gettimeofday(&time, NULL))
        {
            //  Handle error
            return 0;
        }
        return (double)time.tv_sec + (double)time.tv_usec * .000001;
    }
    /*------------------------------------------------------------*/
    double get_cpu_time()
    {
        /*! 
        measure cpu passed time
        \return cpu time in second
        */

        return (double)clock() / CLOCKS_PER_SEC;
    }
    /*------------------------------------------------------------*/
    void display_timing(double wtime, double cptime)
    {
        /*!
        Display wall time and cpu time on terminal
        
        */
        int wh, ch;
        int wmin, cpmin;
        double wsec, csec;
        wh = (int)wtime / 3600;
        ch = (int)cptime / 3600;
        wmin = ((int)wtime % 3600) / 60;
        cpmin = ((int)cptime % 3600) / 60;
        wsec = wtime - (3600. * wh + 60. * wmin);
        csec = cptime - (3600. * ch + 60. * cpmin);
        printf("Wall Time : %d hours and %d minutes and %.4f seconds.\n", wh, wmin, wsec);
        printf ("CPU  Time : %d hours and %d minutes and %.4f seconds.\n",ch,cpmin,csec);
    }

} // namespace Neuro

// from random_generators.hpp
// ----------------------------------------------------------------------------

namespace NTB
{

    std::vector<float> rand_uniform(const double low,
                                    const double high,
                                    const int size,
                                    const int seed = -1)
    {
        /*! 
        * Random number distribution that produces floating-point values according to a uniform distribution, which is described by the following probability density function:
        * P(X|a, b) = 1/(b-a), a<= x < b
        * This distribution (also know as rectangular distribution) produces random numbers in a range [a,b) where all intervals of the same length within it are equally probable.
        * \param low Lower boundary of the output interval. All values generated will be greater than or equal to low.
        * \param high Upper boundary of the output interval. All values generated will be less than or equal to high.
        * \param size Lengh of output random numbers.
        * \param seed if not defined a positive number, return the same random numbers
        * 
        */

        assert(low < high);
        assert(size > 0);

        std::vector<float> numbers(size);

        if (seed >= 0)
        {
            std::default_random_engine generator(seed);
            std::uniform_real_distribution<float> uniform(low, high);
            for (int i = 0; i < size; ++i)
                numbers[i] = uniform(generator);
        }
        else
        {
            std::random_device rd;        //Will be used to obtain a seed for the random number engine
            std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
            std::uniform_real_distribution<float> uniform(low, high);

            for (int i = 0; i < size; ++i)
                numbers[i] = uniform(generator);
        }

        return numbers;
    }

    //-------------------------------------------------------------------------
    std::vector<int> randint(const int low,
                             const int high,
                             const int size,
                             const int seed = -1)
    {
        /*!
        * Random number distribution that produces integer values according to a uniform discrete distribution, which is described by the following probability mass function:
        * P(i|a,b) = 1/(b-a+1), a <= i <= b
        * \param low Lower boundary of the output interval. All values generated will be greater than or equal to low.
        * \param high Upper boundary of the output interval. All values generated will be less than or equal to high.
        * \param size Lengh of output random numbers.
        * \param seed if not defined a positive number, return the same random numbers
        * 
        */
        assert(low < high);
        assert(size > 0);

        std::vector<int> numbers(size);

        if (seed >= 0)
        {
            std::default_random_engine generator(seed);
            std::uniform_int_distribution<int> uniform(low, high);
            for (int i = 0; i < size; ++i)
                numbers[i] = uniform(generator);
        }
        else
        {
            std::random_device rd;        //Will be used to obtain a seed for the random number engine
            std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
            std::uniform_int_distribution<int> uniform(low, high);

            for (int i = 0; i < size; ++i)
                numbers[i] = uniform(generator);
        }

        return numbers;
    }

    //-------------------------------------------------------------------------
} // namespace NTB

// from signal_processing.hpp
// ----------------------------------------------------------------------------

namespace NTB
{
    void make_signal(std::vector<double> &signal,
                     const int fs,
                     const int num_points = 1024,
                     const double f1 = 50.25,
                     const double f2 = 80.5,
                     const double a1 = 1.0,
                     const double a2 = 0.5)
    {
        /*! 
        * Generate two sine waves of different frequencies and amplitudes.
        * 
        * \param signal [input/output] 1d real vector as signal. 
        * \param fs frequency sampling [s^-1]
        * \param num_points the numper of points in signal
        * \param f1 frequency in [Hz]
        * \param f2 frequency in [Hz]
        * \param a1 amplitude
        * \param a2 amplitude
        */

        int i;
        // double dt = 1.0 / fs;
        // unsigned num_points = signal.size();
        signal.resize(num_points);

        for (i = 0; i < num_points; ++i)
        {
            double theta = (double)i / (double)fs;
            signal[i] = a1 * sin(f1 * 2.0 * M_PI * theta) +
                        a2 * sin(f2 * 2.0 * M_PI * theta);
        }
    }

    //-------------------------------------------------------------------------
    void fft(const std::vector<double> &signal,
             std::vector<double> &frequencies,
             std::vector<double> &amplitudes,
             const double fs)
    {
        /*!
        * discrete Fourier transform (DFT) from 1d read signal
        * 
        * \param signal [Input] input signal
        * \param freq  [input/output] output as frequency
        * \param amplitudes [input/output] output as amplitudes
        * \param fs frequency sampling in [s^1]
        * 
        * 
        */

        const int REAL = 0;
        const int IMAG = 1;
        // const double fs = 1.0 / (dt + 0.0);
        const int num_points = signal.size();
        amplitudes.resize(num_points / 2);
        frequencies.resize(num_points / 2) ;
        double *signalArray = new double[num_points];
        unsigned flags{0};

        fftw_complex result[num_points / 2 + 1];
        fftw_plan plan = fftw_plan_dft_r2c_1d(num_points,
                                              signalArray,
                                              result,
                                              flags);
        for (int i = 0; i < num_points; i++)
            signalArray[i] = signal[i];

        fftw_execute(plan);
        for (int i = 0; i < (0.5 * num_points); i++)
        {
            amplitudes[i] = 2.0 / (double)(num_points)*sqrt(result[i][REAL] * result[i][REAL] + result[i][IMAG] * result[i][IMAG]);
            frequencies[i] = i / double(num_points) * fs;
        }

        fftw_destroy_plan(plan);
        delete[] signalArray;
    }

} // namespace NTB


#endif // !NEURO_TOOLBOX
