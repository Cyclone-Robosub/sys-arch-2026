import os
import random
import shutil
import sys

def split_yolo_dataset(dataset_path: str, train_ratio=0.8):
    # Define directories
    img_dir = os.path.join(dataset_path, 'images')
    lbl_dir = os.path.join(dataset_path, 'labels')
    
    # Check if source directories exist
    if not os.path.exists(img_dir) or not os.path.exists(lbl_dir):
        print("Error: 'images' and 'labels' directories not found.")
        return

    # List all images
    images = [f for f in os.listdir(img_dir) if f.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp'))]
    random.seed(42)  # For reproducibility
    random.shuffle(images)

    # Calculate split
    split_idx = int(len(images) * train_ratio)
    train_files = images[:split_idx]
    val_files = images[split_idx:]

    # Directories to create
    splits = ['train', 'val']
    subdirs = ['images', 'labels']

    for s in splits:
        for sd in subdirs:
            os.makedirs(os.path.join(s, sd), exist_ok=True)

    def move_data(file_list, target_split):
        for img_name in file_list:
            # Move Image
            shutil.move(os.path.join(img_dir, img_name), 
                        os.path.join(target_split, 'images', img_name))
            
            # Move corresponding Label (.txt)
            label_name = os.path.splitext(img_name)[0] + '.txt'
            src_label_path = os.path.join(lbl_dir, label_name)
            if os.path.exists(src_label_path):
                shutil.move(src_label_path, 
                            os.path.join(target_split, 'labels', label_name))

    # Perform moves
    move_data(train_files, 'train')
    move_data(val_files, 'val')

    # Cleanup empty source directories if desired
    os.rmdir(img_dir)
    os.rmdir(lbl_dir)

    print(f"Split completed: {len(train_files)} train, {len(val_files)} val.")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python split.py <dataset_path>")
        sys.exit(1)

    dataset_path = sys.argv[1]

    split_yolo_dataset(dataset_path=dataset_path)