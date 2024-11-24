#!/usr/bin/env python3

import os
import pyperclip
import subprocess

def main():
    try:
        # Step 1: Get clipboard content
        clipboard_content = pyperclip.paste()

        # Step 2: Write clipboard content to 'dsp/input'
        input_file_path = "dsp/input"
        with open(input_file_path, "w") as file:
            file.write(clipboard_content)
        print(f"Clipboard content written to {input_file_path}")

        # Step 3: Change directory to 'dsp'
        os.chdir("dsp")
        print("Changed directory to 'dsp'")

        # Step 4: Run './fft.py'
        subprocess.run(["python3", "./fft.py"])
        print("Executed ./fft.py")

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()

