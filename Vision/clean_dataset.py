# Use this file to clean up the labels for yolo keypoint dataset
# for all the keypoint labels, if the visibility is 0, set x and y to 0.5

import os
import sys

def get_label_files(label_dir):
    return [f for f in os.listdir(label_dir) if f.endswith('.txt')]

def write_labels(file_path, labels):
    with open(file_path, 'w') as f:
        for label in labels:
            f.write(' '.join(map(str, label)) + '\n')

def clean_keypoint_labels(label_dir):
    if not os.path.exists(label_dir):
        print(f"Error: Directory '{label_dir}' does not exist")
        sys.exit(1)

    label_files = get_label_files(label_dir)
    print(f"Found {len(label_files)} label files in {label_dir}")

    for label_file in label_files:
        file_path = os.path.join(label_dir, label_file)

        # Read the label file
        with open(file_path, 'r') as f:
            lines = f.readlines()

        cleaned_labels = []
        for line in lines:
            parts = line.strip().split()
            if len(parts) < 6:  # Not enough data for keypoints
                cleaned_labels.append(parts)
                continue

            # First 5 values are: class_id, x_center, y_center, width, height
            cleaned_line = parts[:5]

            # The rest are keypoints in format: x, y, visibility
            keypoints = parts[5:]

            # Process keypoints in groups of 3 (x, y, visibility)
            for i in range(0, len(keypoints), 3):
                if i + 2 < len(keypoints):
                    x = float(keypoints[i])
                    y = float(keypoints[i + 1])
                    visibility = int(keypoints[i + 2])

                    # If visibility is 0, set x and y to 0.5
                    if visibility == 0:
                        x = 0.5
                        y = 0.5

                    cleaned_line.extend([str(x), str(y), str(visibility)])
                else:
                    # Handle incomplete keypoint data
                    cleaned_line.extend(keypoints[i:])

            cleaned_labels.append(cleaned_line)

        # Write back to the file
        write_labels(file_path, cleaned_labels)

    print(f"Successfully cleaned {len(label_files)} label files")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python clean_dataset.py <label_directory>")
        sys.exit(1)

    label_directory = sys.argv[1]
    clean_keypoint_labels(label_directory)