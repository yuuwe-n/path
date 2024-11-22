import csv

def main():
    print("Paste your data below (comma-separated per line). Press Enter twice when done:")

    # Open the output file in write mode
    output_file = "output.csv"
    try:
        with open(output_file, mode="w", newline="") as file:
            writer = csv.writer(file)

            while True:
                try:
                    # Read one line at a time
                    line = input().strip()
                    if line == "":  # Stop on an empty line
                        break

                    # Split the line into values and write as a column
                    writer.writerow(line.split(","))  # Write each line as a row in the file

                except EOFError:  # Handle unexpected EOF
                    break

        print(f"Data saved to {output_file}")

    except Exception as e:
        print(f"Error saving to CSV: {e}")

if __name__ == "__main__":
    main()

