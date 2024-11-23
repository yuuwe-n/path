#!/usr/bin/env python3

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Define constants `mins`, `maxs`, and `weights` (replace with actual values)
mins = [0, 0, 0, 0, 0, 0, 0, 0]  # Minimum values for the sensors
maxs = [1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000]  # Maximum values for the sensors
weights = [-40, -30, -20, -10, 10, 20, 30, 40]  # Example weights, adjust as needed

weights =[-15, -14, -12, -8, 8, 12, 14, 15]
mins = [756, 595,686,503,572,663,641,706]
maxs = [1744,1321,1658,964,1155,1718,1489,1794]

# File path for the CSV file
file_path = 'phase.csv'

# Step 1: Read the CSV file
try:
    data = pd.read_csv(file_path, delimiter='\t', header=None)  # Assuming no header
    if data.shape[1] != 9:
        raise ValueError("Expected 9 columns in the CSV file.")
except Exception as e:
    print(f"Error reading CSV file: {e}")
    exit()

# Extract the output error (Column 1) and sensor values (Columns 2–9)
output_error = data.iloc[:, 0].dropna().to_numpy()  # Column 1: Output error
sensors = data.iloc[:, 1:].dropna(axis=0).to_numpy()  # Columns 2–9: Sensor values

# Step 2: Calculate the error signal using the provided C logic
def calc_error(inputs):
    """
    Calculate the error signal based on the 8 sensor inputs.
    """
    temp = np.zeros(8)
    weighted_sum = 0

    for i in range(8):
        temp[i] = inputs[i] - mins[i]
        if temp[i] <= 0:
            temp[i] = 0
        temp[i] = temp[i] * 1000 / maxs[i]
        weighted_sum += temp[i] * weights[i]
    
    error = weighted_sum / 8
    return error

# Compute the calculated error signal for all rows
calculated_error = np.array([calc_error(row) for row in sensors])

# Step 3: Perform FFT for both errors
d = 1  # Sampling period (adjust this if you know the actual sampling interval)
frequencies = np.fft.fftfreq(len(output_error), d=d)

# FFT of the output error
fft_output_error = np.fft.fft(output_error)
phase_output_error = np.angle(fft_output_error)

# FFT of the calculated error
fft_calculated_error = np.fft.fft(calculated_error)
phase_calculated_error = np.angle(fft_calculated_error)

# Compute the phase difference
phase_difference = phase_output_error - phase_calculated_error

# Plot the phase difference
plt.figure(figsize=(10, 6))
plt.plot(frequencies[:len(frequencies)//2], phase_difference[:len(frequencies)//2])
plt.title("Phase Difference Between Output Error and Calculated Error")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Phase Difference (radians)")
plt.grid()
plt.show()

# Step 4: Save the phase difference for further analysis
try:
    phase_diff_df = pd.DataFrame({
        "Frequency (Hz)": frequencies[:len(frequencies)//2],
        "Phase Difference (radians)": phase_difference[:len(frequencies)//2]
    })
    phase_diff_df.to_csv("error_phase_differences.csv", index=False)
    print("Phase differences saved to 'error_phase_differences.csv'")
except Exception as e:
    print(f"Error saving phase differences: {e}")

