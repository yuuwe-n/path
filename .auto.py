#!/usr/bin/env python3

import pyperclip
import subprocess

def copy_clipboard_to_file(filename="input"):
    try:
        # Get the content from the clipboard
        clipboard_content = pyperclip.paste()
        
        # Write the content to the specified file
        with open(filename, "w") as file:
            file.write(clipboard_content)
        print(f"Clipboard content successfully written to {filename}.")
    except Exception as e:
        print(f"An error occurred while writing to the file: {e}")

def execute_python_file(script_name):
    try:
        # Execute the given Python script
        result = subprocess.run(["python3", script_name], capture_output=True, text=True)
        
        # Print the output from the executed script
        print(f"Output from {script_name}:\n{result.stdout}")
        if result.stderr:
            print(f"Errors from {script_name}:\n{result.stderr}")
    except FileNotFoundError:
        print(f"The script '{script_name}' was not found.")
    except Exception as e:
        print(f"An error occurred while executing the script: {e}")

if __name__ == "__main__":
    # Step 1: Copy clipboard content to "input"
    copy_clipboard_to_file("input")
    
    # Step 2: Execute another Python script (replace "script.py" with your script name)
    execute_python_file(".mod_parse.py")


