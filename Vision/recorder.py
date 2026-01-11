import cv2
import time
import os
import sys

VIDEO_SPAN = 10 # seconds

# Get device index from command line, default to 0
if len(sys.argv) > 1:
    try:
        device_index = int(sys.argv[1])
    except ValueError:
        print("Invalid device index. Using default (0).")
        device_index = 0
else:
    print("Usage: python video_recorder.py [device_index]")
    exit(1)

cap = cv2.VideoCapture(device_index)  # Adjust if using USB camera index or file

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
cap.set(cv2.CAP_PROP_FPS, 15)
cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'MJPG'))
# cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc('H', '2', '6', '4'))

# Verify actual settings
actual_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
actual_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
actual_fps = cap.get(cv2.CAP_PROP_FPS)

print(f"Actual resolution: {actual_width}x{actual_height}")
print(f"Actual FPS: {actual_fps}")

output_folder = 'videos/'
os.makedirs(output_folder, exist_ok=True)

while True:

    frame_idx = 0
    writer = cv2.VideoWriter(
        f'{output_folder}output_{time.strftime("%Y%m%d_%H%M%S")}.avi', 
        cv2.VideoWriter_fourcc(*'MJPG'), 
        15, 
        (1920, 1080))

    while frame_idx < 30 * VIDEO_SPAN:  # Record 100 frames
        ret, frame = cap.read()
        if not ret:
            break

        frame_idx += 1
        print(f"Recording frame {frame_idx}")

        writer.write(frame)

        # Display the frame (optional)
        # cv2.imshow('Frame', frame)
        # if cv2.waitKey(1) & 0xFF == ord('q'):
        #     break

    writer.release()
    # cv2.destroyAllWindows()

cap.release()