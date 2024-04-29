#!/bin/bash

# Check if the user provided a file name
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file_name>"
    exit 1
fi

file_name=$1

# Check if the file exists in the current directory
if [ -e "$file_name" ]; then
    echo "File '$file_name' exists in the current directory."
    exit 0
fi

# Check if the file exists in the entire drive
if find / -name "$file_name" 2>/dev/null; then
    echo "File '$file_name' exists on the drive."
else
    echo "File '$file_name' does not exist in the folder or on the drive."
fi




PS:
To use this script, save it to a file (e.g., file_exists.sh), grant execute permissions using chmod +x file_exists.sh, and then run it with the file name you want to check:
./file_exists.sh <file_name>

Eg:
./file_exists.sh example.txt
