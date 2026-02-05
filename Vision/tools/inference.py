# Use this file to inference on a openCV capture

import cv2 as cv
import numpy as np
import torch
import sys

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

if __name__ == "__main__":

    if (len(sys.argv) < 2):
        print("Usage: python inference.py <source>")

    source = sys.argv[1]
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

        cv.imshow('Inference', frame)
        if cv.waitKey(1) == ord('q'):
            break

    cap.release()
    cv.destroyAllWindows()