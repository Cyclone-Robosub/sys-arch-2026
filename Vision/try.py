from ultralytics import YOLO

model = YOLO('runs/pose/train/weights/last.pt')

model.predict(source='/dataset/val/images/', conf=0.5, save=True)