#ifndef STATISTICS
#define STATISTICS

#include "config.hpp"

namespace NTB
{
    template <typename T>
    std::vector<T> flatten(const std::vector<std::vector<T>> &vec)
    {
        /*!
         * Return a copy of the vector collapsed into one dimension
         * \param vec input vector of vectors
         * \return A copy of the input vector, flattened to one dimension.
         */
        std::size_t total_size = 0;
        for (const auto &sub : vec)
            total_size += sub.size();
        std::vector<T> result;
        result.reserve(total_size);
        for (const auto &sub : vec)
            result.insert(result.end(), sub.begin(), sub.end());
        return result;
    }

    std::vector<double> angle_arr(const fftw_complex *z,
                                  const int n,
                                  bool deg = false)
    {
        /*!
         * Return the angle of the complex argument.
         * 
         */

        constexpr int REAL = 0;
        constexpr int IMAG = 1;
        constexpr double coeff = 180.0 / M_PI;

        std::vector<double> angle_z(n);
        for (int i = 0; i < n; i++)
        {
            std::complex<double> z0(z[i][REAL], z[i][IMAG]);
            if (deg)
                angle_z[i] = std::arg(z0) * coeff;
            else  
                angle_z[i] = std::arg(z0);
        }

        return angle_z;
    }

    template <typename T>
    inline double average(const std::vector<T> &vec,
                          const int index = 0)
    {
        /*!
         * average the vector from element "index" to end of the vector 
         * 
         * \param vec input vector
         * \param index index to drop elements before that
         * \return [double] average value of input vector
         */
        return accumulate(vec.begin() + index,
                          vec.end(), 0.0) /
               (vec.size() - index);
    }

    void hilbert_transform(const std::vector<double> &in_vec,
                           fftw_complex *out_array)
    {
        /*!
         * Compute the analytic signal, using the Hilbert transform.
         * equivalent to scipy.signal.hilbert
         * 
         * \param input vector
         * \param out_array complex analytic signal
         */

        constexpr int REAL = 0;
        constexpr int IMAG = 1;

        // copy data into the complex array
        int N = in_vec.size();
        for (int i = 0; i < N; i++)
        {
            out_array[i][REAL] = in_vec[i];
            out_array[i][IMAG] = 0;
        }
        // create a DFT plan and execute it
        fftw_plan plan = fftw_plan_dft_1d(N,
                                          out_array,
                                          out_array,
                                          FFTW_FORWARD,
                                          FFTW_ESTIMATE);
        fftw_execute(plan);
        fftw_destroy_plan(plan);
        int hN = N >> 1; // half of the length(N/2);
        int numRem = hN; // the number of remaining elements

        // multiply the appropriate values by 2
        // those that sould be multiplied by 1 are left intact because they wouldn't change
        for (int i = 1; i < hN; i++)
        {
            out_array[i][REAL] *= 2;
            out_array[i][IMAG] *= 2;
        }

        // if the length is even, the number of remaining elements decreases by 1
        if (N % 2 == 0)
            numRem--;

        // if it is odd and greater than 1, the middle value must be multiplied by 2
        else if (N > 1)
        {
            out_array[hN][REAL] *= 2;
            out_array[hN][IMAG] *= 2;
        }
        // set the remaining values to 0
        // multiply by 0 gives 0 so we don't care about multiplication
        memset(&out_array[hN + 1][REAL], 0, numRem * sizeof(fftw_complex));

        // create an IDFT plan and execute it
        plan = fftw_plan_dft_1d(N, out_array, out_array, FFTW_BACKWARD, FFTW_ESTIMATE);
        fftw_execute(plan);
        // dom some cleaning
        fftw_destroy_plan(plan);
        fftw_cleanup();

        // scale the IDFT output
        for (int i = 0; i < N; i++)
        {
            out_array[i][REAL] /= N;
            out_array[i][IMAG] /= N;
        }
    }

    std::vector<double> unwrap(const std::vector<double> &in_vec)
    {
        /*!
     * Unwrap by changing deltas between values to 2*pi complement.
     * 
     * Unwrap radian phase in_vec by changing absolute jumps greater than pi to their 2*pi complement.
     * equivalent to numpy.unwrap
     * \param in_vec input vector
     * 
     * \return out_vec output vector
     */

        int len = in_vec.size();
        std::vector<double> out_vec(len);
        out_vec[0] = in_vec[0];
        for (size_t i = 1; i < len; i++)
        {
            double d = in_vec[i] - in_vec[i - 1];
            d = d > M_PI ? d - 2 * M_PI : (d < -M_PI ? d + 2 * M_PI : d);
            out_vec[i] = out_vec[i - 1] + d;
        }
        return out_vec;
    }

    double calculate_phase_difference(const std::vector<double> &x)
    {
        int n = x.size();
        double sum = 0.0;
        for (int i = 1; i < n; i++)
        {
            sum += abs(x[i] - x[0]);
        }
        double result = sum / (n - 1.0);
        return result;
    }

    double calculate_phase_synchrony(const std::vector<std::vector<double>> &voltages)
    {
        int n = voltages.size();
        int nstep = voltages[0].size();
        std::vector<double> delta_phi(nstep);
        std::vector<std::vector<double>> inst_phase(n, std::vector<double>(nstep));

        for (int i = 0; i < n; i++)
        {
            fftw_complex z[nstep];
            hilbert_transform(voltages[i], z);
            std::vector<double> angle_z = angle_arr(z, nstep);
            // inst_phase[i] = unwrap(angle_z);
            for (int j = 0; j < nstep; j++)
                inst_phase[i][j] = fmod(angle_z[j], (2.0 * M_PI));
        }

        for (int j = 0; j < nstep; j++)
        {
            std::vector<double> x(n);
            for (int i = 0; i < n; i++)
                x[i] = inst_phase[i][j];
            delta_phi[j] = calculate_phase_difference(x);
        }
        double result = average(delta_phi, 0);

        return result;
    }
} // namespace NTB

#endif // !STATISTICS