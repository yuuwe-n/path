#!/usr/env/bin python3

import csv

def main():
    print("Paste your data below (comma-separated per line). Press Enter twice when done:")
    
    # Step 1: Collect data from user
    input_data = []
    while True:
        try:
            line = input().strip()
            if line == "":  # Stop input on an empty line
                break
            input_data.append(line.split(","))  # Split the line into values
        except EOFError:  # Handle unexpected EOF
            break

    # Step 2: Transpose rows to columns for the CSV
    transposed_data = list(zip(*input_data))  # Transpose the list of lists
    
    # Step 3: Write to a CSV file
    output_file = "output.csv"
    try:
        with open(output_file, mode="w", newline="") as file:
            writer = csv.writer(file)
            writer.writerows(transposed_data)  # Write transposed data
        print(f"Data saved to {output_file}")
    except Exception as e:
        print(f"Error saving to CSV: {e}")

if __name__ == "__main__":
    main()
#
