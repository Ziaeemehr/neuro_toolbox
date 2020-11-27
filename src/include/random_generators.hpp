#ifndef RANDOM_GENERATORS
#define RANDOM_GENERATORS

#include <vector>
#include <random>
#include <assert.h>

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
            for (size_t i = 0; i < size; ++i)
                numbers[i] = uniform(generator);
        }
        else
        {
            std::random_device rd;  //Will be used to obtain a seed for the random number engine
            std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
            std::uniform_real_distribution<float> uniform(low, high);

            for (size_t i=0; i<size; ++i)
                numbers[i] = uniform(generator);
        }

        return numbers;
    }

    //-------------------------------------------------------------------------
    std::vector<int> randint(const int low,
                             const int high,
                             const int size,
                             const int seed=-1)
    {
        /*!
        * Random number distribution that produces integer values according to a uniform discrete distribution, which is described by the following probability mass function:
        * P(i|a,b) = 1/(b-a+1), a<= i <= b
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
            for (size_t i = 0; i < size; ++i)
                numbers[i] = uniform(generator);
        }
        else
        {
            std::random_device rd;  //Will be used to obtain a seed for the random number engine
            std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
            std::uniform_int_distribution<int> uniform(low, high);

            for (size_t i=0; i<size; ++i)
                numbers[i] = uniform(generator);
        }

        return numbers;
    }

    //-------------------------------------------------------------------------
} // namespace NTB

#endif // !RANDOM_GENERATORS
