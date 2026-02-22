# Use this file to inference on a openCV capture

import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
import torch
import sys
import argparse
from ultralytics import YOLO
from traitlets.traitlets import Integer

MODEL_PATH = 'model.pt' 

def predict(model: YOLO, frame: np.ndarray):
    """
    Precess the input frame from openCV through the model and 
    Return the normalizedkeypoints.
    
    :param model: PyTorch model for inference
    :param frame: Input frame from openCV capture (H x W x C) in BGR format
    :return: Normalized keypoints as a numpy array of shape (num_keypoints, 2)
    """
    results = model.predict(frame, verbose=False)
    if len(results) > 0 and len(results[0].keypoints.xyn) > 0:
        pred_keypoints = results[0].keypoints.xyn[0].cpu().numpy()
    else:
        pred_keypoints = np.array([])

    return pred_keypoints

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

def detect_color_in_roi(frame, point: np.ndarray) -> str:
    if frame is None:
        print("Error: Empty frame passed to function")
        return -1
    # 2. Define the Region of Interest (ROI)
    img_h, img_w = frame.shape[:2]

    # Format is: image[y1:y2, x1:x2]
    x, y, w, h = int(point[0]), int(point[1]), 20, 20
    y1 = max(0, y - h)
    y2 = min(img_h, y + h)
    x1 = max(0, x - w)
    x2 = min(img_w, x + w)
    roi = frame[y1:y2, x1:x2]

    # 3. Convert ROI to HSV color space
    hsv_roi = cv.cvtColor(roi, cv.COLOR_BGR2HSV)

    # 4. Define HSV ranges

    # --- RED RANGES ---
    # Red is special: it wraps around 0 (0-10 and 170-180)
    lower_red1 = np.array([0, 70, 50])
    upper_red1 = np.array([10, 255, 255])

    lower_red2 = np.array([170, 70, 50])
    upper_red2 = np.array([180, 255, 255])

    # --- BLACK RANGE ---
    # Black is defined by low Value (brightness).
    # Hue and Saturation ranges are wide to catch "dark" versions of any color.
    lower_black = np.array([0, 0, 0])
    upper_black = np.array([180, 255, 50]) # V < 50 is typically black

    # 5. Create Masks
    # Check for both red ranges and combine them
    mask_red1 = cv.inRange(hsv_roi, lower_red1, upper_red1)
    mask_red2 = cv.inRange(hsv_roi, lower_red2, upper_red2)
    mask_red = mask_red1 + mask_red2

    # Check for black
    mask_black = cv.inRange(hsv_roi, lower_black, upper_black)

    # 6. Count non-zero pixels to determine color presence
    red_pixels = cv.countNonZero(mask_red)
    black_pixels = cv.countNonZero(mask_black)
    total_pixels = img_w * img_h

    # Threshold: e.g., if > 50% of the ROI is that color
    threshold_percent = 0.50

    if red_pixels > (total_pixels * threshold_percent):
        #print(f"Region is RED ({red_pixels} pixels)")
        return "red"
    elif black_pixels > (total_pixels * threshold_percent):
        #print(f"Region is BLACK ({black_pixels} pixels)")
        return "black"
    elif black_pixels > red_pixels:
        #print("Region is predominately black")
        return "black"
    elif red_pixels > black_pixels:
        #print("Region is predominately red")
        return "red"
    else:
        #print("Region is neither predominately red nor black")
        return "neither"
    
def check_color_keypoints (frame, keypoints: np.ndarray) -> dict:
  # get color around each keypoint and see whether it matches actual gate
  top_left = keypoints[0, 0:2]
  bottom_left = keypoints[1, 0:2]
  top_right = keypoints[2, 0:2]
  bottom_right = keypoints[3, 0:2]

  good_keypoints = {}
  bad_keypoints = {}
  # top left needs to be black
  if detect_color_in_roi(frame, top_left) == "black":
    good_keypoints["top_left"] = top_left
  else:
    bad_keypoints["top_left"] = top_left
  # bottom left needs to be red
  if detect_color_in_roi(frame, bottom_left) == "red":
    good_keypoints["bottom_left"] = bottom_left
  else:
    bad_keypoints["bottom_left"] = bottom_left
  # top right needs to be red
  if detect_color_in_roi(frame, top_right) == "red":
    good_keypoints["top_right"] = top_right
  else:
    bad_keypoints["top_right"] = top_right
  # bottom right needs to be black
  if detect_color_in_roi(frame, bottom_right) == "black":
      good_keypoints["bottom_right"] = bottom_right
  else:
    bad_keypoints["bottom_right"] = bottom_right
  return good_keypoints, bad_keypoints

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

    model = YOLO(MODEL_PATH)

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
        if keypoints.size == 0:
            break

        good_keypoints, bad_keypoints = check_color_keypoints(frame, keypoints)
        w_o, h_o = 40, 40
        if len(good_keypoints) > 0:
            kpts_pixel = np.array(list(good_keypoints.values()))[:, :2] * [w,h]
            # Draw good keypoints on the frame
            for (x, y) in kpts_pixel.astype(int):
                y1 = max(0, y - h_o)
                y2 = min(h, y + h_o)
                x1 = max(0, x - w_o)
                x2 = min(w, x + w_o)
                cv.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                cv.circle(frame, (x, y), 5, (0, 255, 0), -1)

        if len(bad_keypoints) > 0:
            kpts_pixel = np.array(list(bad_keypoints.values()))[:, :2] * [w,h]
            # Draw bad keypoints on the frame
            for (x, y) in kpts_pixel.astype(int):
                y1 = max(0, y - h_o)
                y2 = min(h, y + h_o)
                x1 = max(0, x - w_o)
                x2 = min(w, x + w_o)
                cv.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                cv.circle(frame, (x, y), 5, (0, 0, 255), -1)

        if args.record:
            out.write(frame)

        cv.imshow('Inference', frame)
        if cv.waitKey(1) == ord('q'):
            break

    if args.record:
        out.release()
    cap.release()
    cv.destroyAllWindows()