import cv2
import time
import os
import sys
from flask import Flask, Response

app = Flask(__name__)

VIDEO_SPAN = 10  # seconds
FPS = 15  # only 15 worked...

# Get device index from command line, default to 0
if len(sys.argv) > 1:
    try:
        device_index = int(sys.argv[1])
    except ValueError:
        print("Invalid device index. Using default (0).")
        device_index = 0
else:
    device_index = 0
    print("No device index provided. Using default (0).")

cap = cv2.VideoCapture(device_index, cv2.CAP_V4L2)

cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)
cap.set(cv2.CAP_PROP_FPS, FPS)
cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'MJPG'))

# Verify actual settings
actual_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
actual_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
actual_fps = cap.get(cv2.CAP_PROP_FPS)

print(f"Actual resolution: {actual_width}x{actual_height}")
print(f"Actual FPS: {actual_fps}")

output_folder = 'videos/'
os.makedirs(output_folder, exist_ok=True)

# Global state for recording
writer = None
frame_count = 0
target_frames = FPS * VIDEO_SPAN

def gen():
    """Read, record, and stream camera frames"""
    global writer, frame_count
    
    while True:
        ret, frame = cap.read()
        if not ret:
            print("Failed to read frame")
            break
        
        # Initialize writer if needed
        if writer is None:
            writer = cv2.VideoWriter(
                f'{output_folder}output_{time.strftime("%Y%m%d_%H%M%S")}.avi',
                cv2.VideoWriter_fourcc(*'MJPG'),
                FPS,
                (actual_width, actual_height))
            frame_count = 0
            print(f"Started new recording segment")
        
        # Write frame to file
        writer.write(frame)
        frame_count += 1
        
        # Check if segment is complete
        if frame_count >= target_frames:
            writer.release()
            writer = None
            print(f"Finished recording segment: {frame_count} frames")
        
        # Encode and yield for web streaming
        _, jpg = cv2.imencode('.jpg', frame, [int(cv2.IMWRITE_JPEG_QUALITY), 80])
        if jpg is not None:
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + jpg.tobytes() + b'\r\n')

@app.route('/video')
def video():
    return Response(gen(), mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/')
def index():
    return '<img src="/video" />'

if __name__ == '__main__':
    print("Starting Flask server on http://0.0.0.0:5000")
    try:
        app.run(host="0.0.0.0", port=5000, threaded=False, debug=False)
    except KeyboardInterrupt:
        print("Shutting down...")
        if writer:
            writer.release()
        cap.release()