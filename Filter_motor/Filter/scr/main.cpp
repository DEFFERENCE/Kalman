#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "Kalman_C.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

// Function to generate a noisy square wave signal
std::vector<float> generate_square_wave(float frequency, float amplitude, float duration, int sample_rate, float noise_level) {
    int total_samples = static_cast<int>(duration * sample_rate);
    std::vector<float> signal(total_samples);
    std::default_random_engine generator;
    std::normal_distribution<float> distribution(0.0, noise_level);

    for (int i = 0; i < total_samples; ++i) {
        float t = static_cast<float>(i) / sample_rate;
        float clean_signal = amplitude * (std::sin(2 * M_PI * frequency * t) >= 0 ? 1 : -1);
        float noisy_signal = clean_signal + distribution(generator);
        signal[i] = noisy_signal;
    }

    return signal;
}

int main() {
    float frequency = 5.0f;  // Hz
    float amplitude = 1.0f;
    float duration = 2.0f;   // seconds
    int sample_rate = 500;   // samples per second
    float noise_level = 0.2f;

    std::vector<float> noisy_signal = generate_square_wave(frequency, amplitude, duration, sample_rate, noise_level);

    float initial_est = 0.0;
    float initial_error = 0.5;
    float error_measure = 0.2;
    float threshold = 0.2;

    KalmanFilter kf(initial_est, initial_error, error_measure, threshold);
    std::vector<float> filtered_signal(noisy_signal.size());

    for (size_t i = 0; i < noisy_signal.size(); ++i) {
        kf.get_Signal(noisy_signal[i]);
        filtered_signal[i] = kf.filter();
    }

    // Generate time vector for plotting
    std::vector<float> time(noisy_signal.size());
    for (size_t i = 0; i < time.size(); ++i) {
        time[i] = static_cast<float>(i) / sample_rate;
    }

    // Plot the signals
    plt::figure_size(1200, 600);
    plt::plot(time, noisy_signal, "r-", {{"label", "Noisy Signal"}});
    plt::plot(time, filtered_signal, "b-", {{"label", "Filtered Signal"}});
    plt::xlabel("Time [s]");
    plt::ylabel("Amplitude");
    plt::title("Noisy Square Wave and Kalman Filtered Signal");
    plt::legend();
    plt::show();

    return 0;
}
