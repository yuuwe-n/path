#!/usr/bin/env python3

import csv

def parse_to_columns_with_index(input_text, output_file):
    """
    Parses input text where:
    - Commas separate values within a row.
    - Newlines separate columns.
    Adds an index column starting from 0.
    
    Saves the parsed content into a CSV file.
    """
    # Split the input into lines (columns)
    columns = input_text.strip().split('\n')

    # Split each line into its comma-separated values
    parsed_data = [line.split(',') for line in columns]

    # Transpose the data to align rows with columns
    max_length = max(len(col) for col in parsed_data)
    transposed_data = list(zip(*[col + [''] * (max_length - len(col)) for col in parsed_data]))

    # Add an index column at the beginning of each row
    indexed_data = [[index] + list(row) for index, row in enumerate(transposed_data)]

    # Write to a CSV file
    with open(output_file, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerows(indexed_data)

if __name__ == "__main__":
    print("Paste your data below (comma-separated per line). Press Enter twice when done:\n")

    # Capture multi-line input from the user
    input_lines = []
    while True:
        try:
            line = input()
            if line.strip() == "":
                break
            input_lines.append(line)
        except EOFError:  # Handle Ctrl+D for end-of-input
            break

    input_text = "\n".join(input_lines)
    output_file = "output.csv"

    # Parse and save the input
    parse_to_columns_with_index(input_text, output_file)
    print(f"\nData has been saved to {output_file}.")

