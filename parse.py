#!/usr/bin/env python3

import csv
import sys

def main():
    input_file = "input"  # Input file name
    output_file = "output.csv"  # Output CSV file name

    try:
        csv.field_size_limit(sys.maxsize)  # Handle large CSV rows

        # Step 1: Read data from the input file
        with open(input_file, "r") as file:
            lines = file.readlines()

        # Step 2: Parse and normalize each line into columns
        parsed_data = []
        for line in lines:
            if line.strip():  # Skip empty lines
                values = [value.strip() for value in line.strip().split(",")]
                parsed_data.append(values)

        # Normalize row lengths
        max_length = max(len(row) for row in parsed_data)
        for row in parsed_data:
            row.extend([""] * (max_length - len(row)))  # Add padding for shorter rows

        # Step 3: Transpose rows to columns
        transposed_data = list(zip(*parsed_data))

        # Step 4: Add an index column
        index_column = list(range(len(transposed_data)))  # Generate index column
        transposed_data_with_index = [[idx] + list(row) for idx, row in zip(index_column, transposed_data)]

        # Step 5: Write the transposed data with index to a CSV file
        with open(output_file, "w", newline="") as file:
            writer = csv.writer(file)
            writer.writerow(["Index"] + [f"Column {i+1}" for i in range(len(parsed_data))])  # Header
            writer.writerows(transposed_data_with_index)

        print(f"Data successfully converted and saved to {output_file}")

    except FileNotFoundError:
        print(f"Error: The file '{input_file}' does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()

