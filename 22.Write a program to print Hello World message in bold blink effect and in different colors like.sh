#!/bin/bash

# Define text formatting escape codes
bold=$(tput bold)
blink=$(tput blink)
reset=$(tput sgr0)

# Print "Hello World" in red color, bold, and blink effect
echo -e "${blink}${bold}\033[31mHello World${reset}"

# Print "Hello World" in brown color, bold, and blink effect
echo -e "${blink}${bold}\033[33mHello World${reset}"
