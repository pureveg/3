#!/bin/bash

# Check if the 'finger' command is available
if command -v finger > /dev/null; then
    echo "Displaying users using finger command:"
    finger
elif command -v who > /dev/null; then
    echo "Displaying users using who command:"
    who
else
    echo "Neither 'finger' nor 'who' command is available."
fi


o/P:
Displaying users using finger command:
Login      Name              TTY         Idle    Login Time    Office     Office Phone
user       User Name         tty1                   Apr 20 08:30

Displaying users using who command:
user     tty1         2022-04-20 08:30 (:0)


cmd:
./display_users.sh
