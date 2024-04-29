#!/bin/bash

# Create FIFO using mkfifo command
mkfifo fifo

# Function for writer process
writer_process() {
    echo "Writer process started. Enter text to send (type 'exit' to quit):"
    while IFS= read -r line; do
        if [ "$line" == "exit" ]; then
            break
        fi
        echo "$line" > fifo || { echo "Error writing to FIFO"; break; }
    done
    echo "Writer process ended."
}

# Function for reader process
reader_process() {
    echo "Reader process started. Waiting for data..."
    while true; do
        if read -r line < fifo; then
            echo "Received: $line"
            echo "$line" | tr '[:lower:]' '[:upper:]'
        else
            echo "Error reading from FIFO"
            break
        fi
    done
}

# Run writer process in background
writer_process &

# Run reader process
reader_process < fifo

# Clean up FIFO after processes exit
rm -f fifo






//Execution cmd:
//chmod +x conversion_script.sh
//./conversion_script.sh




