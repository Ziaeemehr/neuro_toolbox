#include "neuro_toolbox.hpp"
#include <algorithm>

int main(int argc, const char **argv)
{

    /*!
     * make a test signal
     */
    std::vector<double> signal;

    int fs = 1024;              //frequency sampling
    double f1 = 50.5;           // frequency1 [Hz]
    double f2 = 80.0;           // frequency2 [Hz]
    double amp1 = 1.1;          // amplitude of frequency1
    double amp2 = 0.5;          // amplitude of frequency2

    int num_points = 4 * 1024;  // number of sample points in signal
    NTB::make_signal(signal, fs, num_points, f1, f2, amp1, amp2);

    /*!
     * DFT from 1D real signal
     */
    std::vector<double> freq;
    std::vector<double> amp;

    NTB::fft(signal, freq, amp, fs);        // apply fft on real 1D signal

    // for (size_t i = 0; i < freq.size(); ++i)
    // {
    //     std::cout << freq[i] << "\t" << amp[i] << "\n";
    // }

    std::vector<double>::iterator result;
    result = std::max_element(amp.begin(), amp.end());
    auto index = std::distance(amp.begin(), result);

    std::cout << "index : " << index << "\n";
    std::cout << "frequency : " << freq[index] << "\n";
    std::cout << "amplitude : " << *result << "\n";

    return 0;
}
