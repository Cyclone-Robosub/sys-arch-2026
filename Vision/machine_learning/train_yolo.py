from ultralytics import YOLO

model = YOLO("yolo26n-pose")

model.train(
    data="/workspace/Vision/sim_dataset/data.yaml",
    epochs=10,
    fliplr=0.0,
    save_period=10,
    batch=20,
)