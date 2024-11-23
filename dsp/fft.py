#!/usr/bin/env python3

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Step 1: Read the CSV file and handle potential issues
#file_path = 'errors.csv'  # Replace with your file path
file_path = 'input'  # Replace with your file path
try:
    # Read the CSV file, ignoring headers and forcing conversion to numeric
    errors = pd.read_csv(file_path, header=None).squeeze("columns")
    errors = pd.to_numeric(errors, errors='coerce').dropna().to_numpy()  # Drop non-numeric entries
except Exception as e:
    print(f"Error reading CSV file: {e}")
    exit()

# Step 2: Perform FFT
try:
    fft_values = np.fft.fft(errors)
    d = 1 # sampling period
    d= 6e-3
    frequencies = np.fft.fftfreq(len(errors), d)  # Replace 'd' with sampling period if known
    fft_magnitude = np.abs(fft_values)
except Exception as e:
    print(f"Error performing FFT: {e}")
    exit()

# Step 3: Plot the FFT

# Calculate low-frequency energy
low_freq_energy = np.sum(fft_magnitude[:10])  # Adjust range as needed
print(f"Low-frequency energy: {low_freq_energy}")

# Calculate high-frequency energy
high_freq_energy = np.sum(fft_magnitude[40:])  # Adjust range for high frequencies
print(f"High-frequency energy: {high_freq_energy}")


plt.figure(figsize=(10, 6))
plt.plot(frequencies[:len(frequencies)//2], fft_magnitude[:len(frequencies)//2])  # Only positive frequencies
plt.title("Frequency Spectrum of Error Signal")
plt.xlabel("Normalized Frequency")
plt.ylabel("Amplitude")
plt.grid()
plt.show()



