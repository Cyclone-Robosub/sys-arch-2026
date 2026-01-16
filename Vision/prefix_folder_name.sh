#!/bin/bash

# Get the name of the current directory
folder_name=$(basename "$PWD")

# Rename all files in the current directory with the folder name as prefix
rename "s/^/${folder_name}_/" *.txt
