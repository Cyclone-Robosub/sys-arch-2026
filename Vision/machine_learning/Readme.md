# Machine Learning For Vision
We are using YOLO from ultralytics for out keypoint and object (bounding box) detection.

## Preparation
For dataset generated from unreal engine. Use [`convert_to_yolo.py`](../tools/convert_to_yolo.py) to convert the dataset to YOLO format. You may need to use [`clean_dataset.py`](../tools/clean_dataset.py) to clean the dataset because ultralytics is stupid that it requires the keypoints not visible to be normalized to [0, 1].