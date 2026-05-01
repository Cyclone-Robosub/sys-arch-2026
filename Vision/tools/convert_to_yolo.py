import pandas as pd
import argparse
import os

INPUT_COLUMNS = ['category', 
                  'top_left_x', 'top_left_y', 'vis_0',
                  'bottom_left_x', 'bottom_left_y', 'vis_1',
                  'bottom_right_x', 'bottom_right_y', 'vis_2',
                  'top_right_x', 'top_right_y', 'vis_3'
                ]

IMG_WIDTH = 1920
IMG_HEIGHT = 1080

def write_yolo_format(file_path: str, data: pd.DataFrame):
    with open(file_path, 'w') as f:
        for _, row in data.iterrows():
            bbox = f"{row['category']} {row['x_center']} {row['y_center']} {row['width']} {row['height']} "
            kpts = f"{row['top_left_x']} {row['top_left_y']} {row['vis_0']} " \
                     f"{row['bottom_left_x']} {row['bottom_left_y']} {row['vis_1']} " \
                     f"{row['bottom_right_x']} {row['bottom_right_y']} {row['vis_2']} " \
                     f"{row['top_right_x']} {row['top_right_y']} {row['vis_3']}\n"
            line = bbox + kpts
            f.write(line)

def convert(csv_dataFrame: pd.DataFrame) -> pd.DataFrame:
    converted = csv_dataFrame.copy()

    x_columns = ['top_left_x', 'bottom_left_x', 'bottom_right_x', 'top_right_x']
    y_columns = ['top_left_y', 'bottom_left_y', 'bottom_right_y', 'top_right_y']

    x_min = converted[x_columns].min(axis=1)
    x_max = converted[x_columns].max(axis=1)
    y_min = converted[y_columns].min(axis=1)
    y_max = converted[y_columns].max(axis=1)

    converted['x_center'] = ((x_min + x_max) / 2) / IMG_WIDTH
    converted['y_center'] = ((y_min + y_max) / 2) / IMG_HEIGHT
    converted['width'] = (x_max - x_min) / IMG_WIDTH
    converted['height'] = (y_max - y_min) / IMG_HEIGHT

    # map visibility 1 to 2
    for vis_col in ['vis_0', 'vis_1', 'vis_2', 'vis_3']:
        converted[vis_col] = converted[vis_col].replace(1, 2)

    for column in x_columns:
        converted[column] = converted[column] / IMG_WIDTH

    for column in y_columns:
        converted[column] = converted[column] / IMG_HEIGHT

    return converted

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Convert CSV labels to YOLO format.')
    parser.add_argument('csv_folder', help='Folder containing CSV label files')
    parser.add_argument('output_folder', nargs='?', help='Folder to write converted labels')
    args = parser.parse_args()

    file_names = []
    csv_labels = []
    for input_file in [os.path.join(args.csv_folder, f) for f in os.listdir(args.csv_folder) if f.endswith('.csv')]:
        df = pd.read_csv(input_file, header=None, names=INPUT_COLUMNS)
        file_names.append(input_file.replace('.csv', '.txt'))
        csv_labels.append(df)

    all_labels = pd.concat(csv_labels, ignore_index=True)
    all_labels['file_names'] = file_names

    converted_labels = convert(all_labels)

    os.makedirs(args.output_folder, exist_ok=True)
    for file_name, group in converted_labels.groupby('file_names'):
        output_file = os.path.join(args.output_folder, os.path.basename(file_name)) if args.output_folder else file_name
        write_yolo_format(output_file, group)

            



    
