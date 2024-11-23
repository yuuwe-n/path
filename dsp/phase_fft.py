#!/usr/bin/env python3

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# File path for the CSV file
file_path = 'phase.csv'  # Update this to your actual file path if needed

# Step 1: Read the CSV file
try:
    # Load the CSV file
    data = pd.read_csv(file_path, delimiter='\t')
    if data.shape[1] != 9:
        print(data.shape[1])
        raise ValueError("Expected 9 columns in the CSV file.")
except Exception as e:
    print(f"Error reading CSV file: {e}")
    exit()

# Extract the error signal and the 8 other signals
error_signal = data.iloc[:, 0].dropna().to_numpy()  # First column is error
comparison_signals = data.iloc[:, 1:].dropna(axis=0).to_numpy()  # Remaining 8 columns

# Ensure all signals have the same length as the error signal
comparison_signals = comparison_signals[:, :len(error_signal)]

# Step 2: Perform FFT for error signal and comparison signals
d = 1  # Sampling period (adjust this if you know the actual sampling interval)
frequencies = np.fft.fftfreq(len(error_signal), d=d)

# FFT of the error signal
fft_error = np.fft.fft(error_signal)
phase_error = np.angle(fft_error)

# Step 3: Compute FFT for each of the 8 comparison signals
phase_differences = []

for i in range(8):
    fft_signal = np.fft.fft(comparison_signals[:, i])
    phase_signal = np.angle(fft_signal)
    phase_diff = phase_error - phase_signal  # Phase difference
    phase_differences.append(phase_diff)

    # Plot phase difference
    plt.figure(figsize=(10, 6))
    plt.plot(frequencies[:len(frequencies)//2], phase_diff[:len(frequencies)//2], label=f"Signal {i+1}")
    plt.title(f"Phase Difference Between Error and Signal {i+1}")
    plt.xlabel("Frequency (Hz)")
    plt.ylabel("Phase Difference (radians)")
    plt.legend()
    plt.grid()
    plt.show()

# Step 4: Save the phase differences for further analysis
try:
    phase_diff_df = pd.DataFrame(phase_differences).transpose()
    phase_diff_df.columns = [f"Signal {i+1}" for i in range(8)]
    phase_diff_df.to_csv("phase_differences.csv", index=False)
    print("Phase differences saved to 'phase_differences.csv'")
except Exception as e:
    print(f"Error saving phase differences: {e}")

