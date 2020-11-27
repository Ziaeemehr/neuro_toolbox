#define CATCH_CONFIG_MAIN
#include "neuro_toolbox.hpp"
#include "catch.hpp"
#include <vector>
#include <algorithm>

TEST_CASE("make a test signal ", " ")
{
    std::vector<double> signal;
    int fs = 100;
    int num_points = 1024;

    NTB::make_signal(signal, fs, num_points);

    // for (auto i:signal)
    //     std::cout << i << "\n";

    double sum = std::accumulate(signal.begin(), signal.end(), 0.0);
    // std::cout << sum << "\n";
    REQUIRE(std::abs(sum + 0.556) < 0.1);
}

TEST_CASE("DFT from 1D real signal", " ")
{
    std::vector<double> signal;
    
    int fs = 1024;
    double f1 = 50.0;
    double f2 = 80.0;
    double amp1 = 1.0;
    double amp2 = 0.5;

    int num_points = 4 * 1024;

    NTB::make_signal(signal, fs, num_points, f1, f2, amp1, amp2);
    std::vector<double> freq;
    std::vector<double> amp;

    NTB::fft(signal, freq, amp, fs);

    // for (size_t i = 0; i < freq.size(); ++i)
    // {
    //     std::cout << freq[i] << "\t" << amp[i] << "\n";
    // }
    
    std::vector<double>::iterator result;
    result = std::max_element(amp.begin(), amp.end());
    auto index = std::distance(amp.begin(), result);
    
    // std::cout << index << "\n";
    // std::cout << freq[index] << "\n";

    double freq_of_max_amp = freq[index];

    REQUIRE(std::abs(freq_of_max_amp - f1) < 0.1);
}

// single file compilation
// g++ -o signal_processing_test signal_processing_test.cpp -Wall -I../include -lfftw3