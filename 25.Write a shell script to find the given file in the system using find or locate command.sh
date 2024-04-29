#!/bin/bash

# Check if the user provided a file name
if [ $# -ne 1 ]; then
    echo "Usage: $0 <file_name>"
    exit 1
fi

file_name=$1

# Search for the file using the find command
echo "Searching for '$file_name' using find command:"
find / -name "$file_name" 2>/dev/null


O/p:
$ ./find_file.sh example.txt
Searching for 'example.txt' using find command:
/home/user/example.txt


Cmd:
./find_file.sh <file_name>
