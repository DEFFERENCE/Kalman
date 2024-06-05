from scipy import signal
import matplotlib.pyplot as plt
import numpy as np
import math

# Functions for Kalman filter operations
def Kalman_Gain(Error_Est, Error_Measure):
    return Error_Est / (Error_Est + Error_Measure)

def Est_current(KG, Mea, Est_before):
    return Est_before + KG * (Mea - Est_before)

def Error_Est_current(KG, Error_Est_before):
    return (1 - KG) * Error_Est_before

# Function to generate a noisy square wave signal
def generate_square_wave(frequency, amplitude, duration, sample_rate, noise_level):
    t = np.linspace(0, duration, int(sample_rate * duration), endpoint=False)
    signal = amplitude * np.sign(np.sin(2 * np.pi * frequency * t))
    
    noise = np.random.normal(0, noise_level, signal.shape)
    noisy_signal = signal + noise
    
    return t, noisy_signal

# Function to plot the signal
def plot_signal(t, signal, title='Square Wave Signal'):
    plt.figure(figsize=(10, 4))
    plt.plot(t, signal, label='Noisy Signal')
    plt.title(title)
    plt.xlabel('Time [s]')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.legend()
    plt.show()

# Parameters
frequency = 4  # Hz
amplitude = 4.0
duration = 4.0  # seconds
sample_rate = 500  # samples per second
noise_level = 0.2
threshold = 0.2 # Threshold for noise detection

# Generate and plot the noisy square wave signal
t, noisy_signal = generate_square_wave(frequency, amplitude, duration, sample_rate, noise_level)
# plot_signal(t, noisy_signal)  # Optional: plot the noisy signal

# Kalman filter initialization
Initial_EST = noisy_signal[0]
Initial_Error = 0.5
Error_Meas = 0.2
Estimate_High = Initial_EST
Estimate_low = -Initial_EST
Error_Est_before_Low = Initial_Error
Error_Est_before_High = Initial_Error
Err_Est_current_Low = Initial_Error
Err_Est_current_High = Initial_Error
estimates = []

# Apply the Kalman filter
# Apply the Kalman filter
for i in range(len(t)):
    Mea = noisy_signal[i]
    if Mea >= threshold:
        KG_High = Kalman_Gain(Err_Est_current_High, Error_Meas)
        Estimate_High = Est_current(KG_High, Mea, Estimate_High) 
        Err_Est_current_High = Error_Est_current(KG_High, Error_Est_before_High)
        Error_Est_before_High = Err_Est_current_High
        estimates.append(Estimate_High)
    elif Mea <= -threshold:
        KG_Low = Kalman_Gain(Err_Est_current_Low, Error_Meas)
        Estimate_low = Est_current(KG_Low, Mea, Estimate_low)   
        Err_Est_current_Low = Error_Est_current(KG_Low, Error_Est_before_Low)
        Error_Est_before_Low = Err_Est_current_Low
        estimates.append(Estimate_low)
    else:
        estimates.append(Mea)


estimates = np.array(estimates)

# Plot the results
plt.figure(figsize=(12, 6))
plt.plot(t, noisy_signal, label='Noisy Signal')
plt.plot(t, estimates, label='Kalman Filter Estimate', linestyle='dotted')
plt.title('Kalman Filter Applied to Noisy Square Wave Signal')
plt.xlabel('Time [s]')
plt.ylabel('Amplitude')
plt.legend()
plt.grid(True)
plt.show()
