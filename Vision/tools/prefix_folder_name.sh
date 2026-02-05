#!/bin/bash

# Loop through all subdirectories in the current directory
for subdir in */; do
    # Get the subdirectory name without trailing slash
    folder_name=$(basename "$subdir")
    
    cd "$subdir" || continue
    # Rename all .txt files in the subdirectory with the folder name as prefix
    rename "s/^/${folder_name}_/" *.jpg *.jpeg *.png

    cd ..
done
