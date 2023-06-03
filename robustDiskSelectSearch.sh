#!/bin/bash

# Check for required commands
for cmd in lsblk grep awk g++; do
  if ! command -v $cmd &> /dev/null; then
    echo "$cmd could not be found. Please install it and try again."
    exit 1
  fi
done

# Compile the C++ program if it hasn't been compiled yet
if [ ! -f IDDFileSearch_Extension ]; then
    g++ -std=c++17 IDDFileSearch_Extension.cpp -o IDDFileSearch_Extension
    if [ $? -ne 0 ]; then
        echo "Compilation failed. Please check your C++ code."
        exit 1
    fi
fi

# Get a list of mounted filesystems
disks=$(lsblk -dlnp | grep part | awk '{print $1, "(" $4 ")"}')

# If no disks are found, exit the script
if [ -z "$disks" ]; then
    echo "No disks found. Please check your system."
    exit 1
fi

# Prompt the user to select a disk
PS3="Please select a disk to search: "
IFS=$'\n'
select disk in $disks
do
    # When a disk is selected, ask for the other parameters and run the C++ program
    if [ -n "$disk" ]; then
        read -p "Enter target extension: " extension
        read -p "Enter max depth: " depth
        diskPath=$(echo $disk | awk '{print $1}') # Get the disk path from the selected option
        ./IDDFileSearch_Extension $extension $diskPath $depth
        if [ $? -ne 0 ]; then
            echo "Search failed. Please check your parameters."
            exit 1
        fi
    fi
    break
done
