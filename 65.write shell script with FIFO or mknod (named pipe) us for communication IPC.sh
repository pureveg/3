#!/bin/bash

# Create FIFO using mkfifo command
mkfifo fifo

# Function for writer process
writer_process() {
    echo "Writer process started. Enter text to send:"
    while IFS= read -r line; do
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
        else
            echo "Error reading from FIFO"
            break
        fi
    done
}

# Run writer process in background
writer_process &

# Run reader process
reader_process

# Clean up FIFO after processes exit
rm -f fifo





//Execution cmd:
//chmod +x communication_script.sh
//./communication_script.sh


//victus@victus-by-HP-Gaming-Laptop-15-fb0xxx:~/Desktop/wce/unix/13a2$ touch mknod.sh
//victus@victus-by-HP-Gaming-Laptop-15-fb0xxx:~/Desktop/wce/unix/13a2$ vim mknod.sh
//victus@victus-by-HP-Gaming-Laptop-15-fb0xxx:~/Desktop/wce/unix/13a2$ chmod +x mknod.sh
//victus@victus-by-HP-Gaming-Laptop-15-fb0xxx:~/Desktop/wce/unix/13a2$ ./mknod.sh
//Writer process started. Enter text to send:
//Reader process started. Waiting for data...
//HELLO
//Received: HELLO



