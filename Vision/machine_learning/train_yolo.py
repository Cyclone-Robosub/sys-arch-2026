from ultralytics import YOLO

model = YOLO("yolo26n-pose")

model.train(
    data="/workspace/Vision/dataset/data.yaml",
    epochs=50,
    fliplr=0.0,
    save_period=10,
    batch=32,
    patience=20
)