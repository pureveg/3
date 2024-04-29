#!/bin/bash

# Check if the user provided a URL
if [ $# -ne 1 ]; then
    echo "Usage: $0 <url>"
    exit 1
fi

url=$1

# Download the webpage using wget
echo "Downloading webpage from $url ..."
wget -q "$url" -O downloaded_page.html

echo "Webpage downloaded successfully. You can find it in downloaded_page.html."


o/P:
For example, if you run the script with the URL https://www.example.com:

Downloading webpage from https://www.example.com ...
Webpage downloaded successfully. You can find it in downloaded_page.html.


cmd:
./download_webpage.sh <url>
