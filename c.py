import csv

def main():
    input_file = "input"  # Input file name
    output_file = "output.csv"  # Output CSV file name

    try:
        # Step 1: Read data from the input file
        with open(input_file, "r") as file:
            raw_data = file.read()

        # Step 2: Parse the data by commas into a list
        values = [value.strip() for value in raw_data.split(",")]

        # Step 3: Write the values into a single column in the CSV file
        with open(output_file, "w", newline="") as file:
            writer = csv.writer(file)
            for value in values:
                writer.writerow([value])  # Write each value into its own row

        print(f"Data successfully converted and saved to {output_file}")

    except FileNotFoundError:
        print(f"Error: The file '{input_file}' does not exist.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()

