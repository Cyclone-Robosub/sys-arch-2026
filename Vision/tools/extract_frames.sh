#!/bin/bash

# get the file path from the first argument
input_path="$1"

file_name=$(basename "$input_path")
file_name="${file_name%.*}"

ffmpeg -i "$input_path" "${file_name}_frame_%06d.jpg"