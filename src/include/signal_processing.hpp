#ifndef SIGNAL_PROCESSING
#define SIGNAL_PROCESSING

#include <vector>
#include <cmath>
#include <fftw3.h>
#include <assert.h>

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

#endif // !SIGNAL_PROCESSING