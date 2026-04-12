# Use this file to inference on a openCV capture
import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
import torch
import sys
import argparse
from ultralytics import YOLO

MODEL_PATH = 'best.pt' 

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
    
    :param image: Input image in RGB fo1rmat
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

def distance_angle(keypoints):
    # Physical focal length / pixel size
    f_air = 2.97 / 0.0028
    # Refractive index of water (n ≈ 1.333)
    n_water = 1.45
    f_underwater = f_air * n_water
    # Center for 1080p
    cx, cy = 960, 540

    camera_matrix = np.array([
        [f_underwater, 0, cx],
        [0, f_underwater, cy],
        [0, 0, 1]
    ], dtype=np.float32)

    dist_coeffs = np.zeros((4,1))

    w, h = 3.048, 1.524
    object_points = np.array([
        [-w/2,  h/2, 0], # Top-Left
        [ w/2,  h/2, 0], # Top-Right
        [ w/2, -h/2, 0], # Bottom-Right
        [-w/2, -h/2, 0]  # Bottom-Left
    ], dtype=np.float32)

    image_points = keypoints

    success, rvec, tvec = cv.solvePnP(
        object_points, 
        image_points, 
        camera_matrix, 
        dist_coeffs,
        flags=cv.SOLVEPNP_ITERATIVE
    )

    if success:
        rmat, _ = cv.Rodrigues(rvec)
        yaw = np.degrees(np.arctan2(-rmat[2,0], np.sqrt(rmat[2,1]**2 + rmat[2,2]**2)))
        pitch = np.degrees(np.arctan2(rmat[2,1], rmat[2,2]))
        
        total_dist = np.linalg.norm(tvec)
        return {
            "distance": total_dist,
            "yaw": yaw,
            "pitch": pitch
        }

if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Run inference on a video source")
    parser.add_argument("source", help="Video source (file path or camera index)")
    parser.add_argument("-m", "--model_path", type=str, default=MODEL_PATH, help="Path to the YOLO model checkpoint")
    parser.add_argument("-o", "--output_path", type=str, default='output.mp4', help="Optional output file path to save the recorded video")
    args = parser.parse_args()

    source = args.source
    cap = cv.VideoCapture(source)
    if not cap.isOpened():
        print("Error opening video stream or file")
        sys.exit(1)

    model = YOLO(args.model_path, task='pose')

    if args.output_path:
        fps = cap.get(cv.CAP_PROP_FPS) 
        fourcc = cv.VideoWriter_fourcc(*'mp4v')
        out = cv.VideoWriter(args.output_path, fourcc, fps, (int(cap.get(3)), int(cap.get(4))))
    
    fps = cap.get(cv.CAP_PROP_FPS)
    frame_count = 0

    while cap.isOpened():
        ok, frame = cap.read()
        if not ok:
            print("Can't receive frame (stream end?). Exiting ...")
            break

        frame_count += 1
        
        elapsed_seconds = frame_count / fps
        
        minutes = int(elapsed_seconds // 60)
        seconds = int(elapsed_seconds % 60)
        millis = int((elapsed_seconds - int(elapsed_seconds)) * 100)
        timer_text = f"Time: {minutes:02d}:{seconds:02d}.{millis:02d}"

        h, w, _ = frame.shape
        timer_position = (w - 250, 50) 
        
        cv.putText(
            frame, 
            timer_text, 
            timer_position, 
            cv.FONT_HERSHEY_SIMPLEX, 
            0.8,               
            (255, 255, 255),    
            2,                 
            cv.LINE_AA
        )

        h, w, _ = frame.shape
        keypoints = predict(model, frame)
        if len(keypoints) > 0:
            kpts_pixel = keypoints[:, :2] * [w, h]

            # Draw keypoints on the frame
            for (x, y) in kpts_pixel.astype(int):
                cv.circle(frame, (x, y), 5, (0, 255, 0), -1)

            if len(keypoints) == 4:
                margin = 5
                on_edge = np.any((kpts_pixel[:, 0] <= margin) | (kpts_pixel[:, 0] >= w - margin) |
                                (kpts_pixel[:, 1] <= margin) | (kpts_pixel[:, 1] >= h - margin))

                if not on_edge:
                    pixel_coords = kpts_pixel[[0, 2, 3, 1]].astype(np.float32)
                    da = distance_angle(pixel_coords)
                    
                    if da:
                        dist_m = da.get('distance')
                        yaw = da.get('yaw')
                        pitch = da.get('pitch')

                        dist_str = f"Distance: {dist_m:.2f}m"
                        angle_str= f"Yaw: {yaw:.1f}  Pitch: {pitch:.1f}"
                        
                        cv.putText(frame, dist_str, (50, 50), 
                                cv.FONT_HERSHEY_SIMPLEX, 1.0, (0, 255, 0), 2, cv.LINE_AA)
                        cv.putText(frame, angle_str, (50, 85), 
                                cv.FONT_HERSHEY_SIMPLEX, 1.0, (0, 255, 0), 2, cv.LINE_AA)
                    else:  
                        cv.putText(frame, "OUT OF BOUNDS", (50, 50), 
                                cv.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 255), 2, cv.LINE_AA)
                else:  
                    cv.putText(frame, "OUT OF BOUNDS", (50, 50), 
                            cv.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 255), 2, cv.LINE_AA)
            else:  
                cv.putText(frame, "OUT OF BOUNDS", (50, 50), 
                        cv.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 255), 2, cv.LINE_AA)
        else:  
            cv.putText(frame, "OUT OF BOUNDS", (50, 50), 
                    cv.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 255), 2, cv.LINE_AA)
        
        if args.output_path:
            out.write(frame)

        cv.imshow('Inference', frame)
        if cv.waitKey(1) == ord('q'):
            break

    if args.output_path:
        out.release()
    cap.release()
    cv.destroyAllWindows()