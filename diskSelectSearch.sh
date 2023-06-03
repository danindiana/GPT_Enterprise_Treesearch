#!/bin/bash

# Compile the C++ program if it hasn't been compiled yet
if [ ! -f IDDFileSearch_Extension ]; then
    g++ -std=c++17 IDDFileSearch_Extension.cpp -o IDDFileSearch_Extension
fi

# Get a list of mounted filesystems
disks=$(lsblk -dlnp | grep part | awk '{print $1, "(" $4 ")"}')

# Prompt the user to select a disk
PS3="Please select a disk to search: "
select disk in $disks
do
    # When a disk is selected, ask for the other parameters and run the C++ program
    if [ -n "$disk" ]; then
        read -p "Enter target extension: " extension
        read -p "Enter max depth: " depth
        ./IDDFileSearch_Extension $extension $disk $depth
    fi
    break
done
