#!/usr/bin/env python3

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.ndimage import gaussian_filter

# Step 1: Read the CSV file and handle potential issues
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
    d = 6e-3  # Sampling period in seconds
    frequencies = np.fft.fftfreq(len(errors), d)  # Frequency axis
    fft_magnitude = np.abs(fft_values)
except Exception as e:
    print(f"Error performing FFT: {e}")
    exit()

# Step 3: Apply Gaussian smoothing
#sigma = 2  # Standard deviation for Gaussian kernel (adjust for smoothing level)
sigma = 0.5
fft_magnitude_smoothed = gaussian_filter(fft_magnitude[:len(frequencies)//2], sigma=sigma)

# Step 4: Plot the FFT (Original and Smoothed)
plt.figure(figsize=(10, 6))
plt.plot(frequencies[:len(frequencies)//2], fft_magnitude[:len(frequencies)//2], alpha=0.5, label="Original FFT")
plt.plot(frequencies[:len(frequencies)//2], fft_magnitude_smoothed, label="Gaussian Smoothed FFT")
plt.title("Frequency Spectrum of Error Signal (Gaussian Smoothing)")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Amplitude")
plt.grid()
plt.legend()
plt.show()

