#!/bin/bash

# Define the target IP address to ping
target_ip="8.8.8.8"  # Google's public DNS server

# Ping the target IP address with a single packet and a timeout of 1 second
ping -c 1 -W 1 $target_ip > /dev/null 2>&1

# Check the exit status of the ping command
if [ $? -eq 0 ]; then
    echo "System is connected to the network"
else
    echo "System is not connected to the network"
fi
