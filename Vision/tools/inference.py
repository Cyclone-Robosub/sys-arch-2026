# Use this file to inference on a openCV capture

import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
import torch
import sys
import argparse

MODEL_PATH = 'model_with_norm_traced.pt'

def predict(model: torch.jit.ScriptModule, frame: np.ndarray):
    """
    Precess the input frame from openCV through the model and 
    Return the normalizedkeypoints.
    
    :param model: PyTorch model for inference
    :param frame: Input frame from openCV capture (H x W x C) in BGR format
    :return: Normalized keypoints as a numpy array of shape (num_keypoints, 2)
    """
    # resize the frame to model input size
    frame = cv.resize(frame, (224, 224))

    # Preprocess the frame
    input_tensor = torch.from_numpy(frame).float().permute(2, 0, 1).unsqueeze(0) / 255.0

    # Run inference
    with torch.no_grad():
        output = model(input_tensor)

    keypoints = output.detach().cpu().numpy().reshape(-1, 2)

    return keypoints

def visualize(image: np.ndarray, keypoints: np.ndarray, title="Image"):
    """
    visualize the image with keypoints overlaid using matplotlib.
    
    :param image: Input image in RGB format
    :param keypoints: Normalized keypoints as a numpy array of shape (num_keypoints, 2)
    :param title: Title for the plot
    """
    
    plt.figure(figsize=(8, 8))
    plt.imshow(image)

    # Keypoints might be a list or array
    kpts = np.array(keypoints)
    if len(kpts) > 0:
        # Scatter plot for keypoints (x, y)
        plt.scatter(kpts[:, 0], kpts[:, 1], c='red', s=40, marker='o')
    plt.axis('off')
    plt.show()

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Run inference on a video source")
    parser.add_argument("source", help="Video source (file path or camera index)")
    parser.add_argument("--record", type=str, default=None, help="Optional output file path to save the recorded video")
    args = parser.parse_args()

    source = args.source
    cap = cv.VideoCapture(source)
    if not cap.isOpened():
        print("Error opening video stream or file")
        sys.exit(1)

    try:
        model = torch.jit.load(MODEL_PATH)
        model.eval()
    except Exception as e:
        print(f"Error loading model: {e}")
        sys.exit(1)

    if args.record:
        fps = cap.get(cv.CAP_PROP_FPS) 
        fourcc = cv.VideoWriter_fourcc(*'mp4v')
        out = cv.VideoWriter(args.record, fourcc, fps, (int(cap.get(3)), int(cap.get(4))))

    while cap.isOpened():
        ok, frame = cap.read()
        if not ok:
            print("Can't receive frame (stream end?). Exiting ...")
            break

        h, w, _ = frame.shape
        keypoints = predict(model, frame)
        kpts_pixel = keypoints[:, :2] * [w, h]

        # Draw keypoints on the frame
        for (x, y) in kpts_pixel.astype(int):
            cv.circle(frame, (x, y), 5, (0, 255, 0), -1)

        if args.record:
            out.write(frame)

        cv.imshow('Inference', frame)
        if cv.waitKey(1) == ord('q'):
            break

    if args.record:
        out.release()
    cap.release()
    cv.destroyAllWindows()