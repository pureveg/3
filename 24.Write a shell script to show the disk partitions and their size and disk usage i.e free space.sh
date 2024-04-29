#!/bin/bash

# Display disk partitions and their sizes
echo "Disk partitions and their sizes:"
df -h

# Display disk usage (free space)
echo -e "\nDisk usage (free space):"
df -h --output=source,size,avail


Output:
Disk partitions and their sizes:
Filesystem      Size  Used Avail Use% Mounted on
/dev/sda1        20G   10G   8.8G  54% /
/dev/sda2        30G   12G    16G  44% /home
/dev/sdb1       100G   20G    80G  20% /data

Disk usage (free space):
Filesystem      Size  Avail
/dev/sda1        20G   8.8G
/dev/sda2        30G    16G
/dev/sdb1       100G    80G


Cmd:
./disk_info.sh
