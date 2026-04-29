# vision

ROS 2 package containing vision nodes for the robot.

| Node | Description |
|---|---|
| `camera_feed_node` | Ingests a raw H264 camera stream, forwards it to mediaMTX via RTSP, and publishes decoded frames as a ROS image topic |
| `keypoint_node` | Runs a TorchScript keypoint-detection model on an image source and publishes detections |

## Dependencies

- ROS 2 Jazzy
- GStreamer 1.0 + gstreamer-app (camera_feed_node)
- LibTorch C++ API (keypoint_node)
- OpenCV, cv_bridge

Install system dependencies:

```bash
# added to the Dockerfile
sudo apt install \
  libopencv-dev \
  ros-jazzy-cv-bridge \
  libgstreamer1.0-dev \
  libgstreamer-plugins-base1.0-dev \
  gstreamer1.0-plugins-good \
  gstreamer1.0-plugins-bad \
  gstreamer1.0-rtsp
```

Download LibTorch from [pytorch.org](https://pytorch.org/get-started/locally/) (select LibTorch, C++, Linux) and extract it:

```bash
unzip libtorch-*.zip -d /opt/
```

## Building

Source ROS and build the package:

```bash
source /opt/ros/jazzy/setup.bash
colcon build --packages-select vision \
  --cmake-args \
    -DTorch_DIR=/opt/libtorch/share/cmake/Torch
```

In container on Jetson Nano:

```bash
colcon build --packages-select vision --cmake-args -DCMAKE_PREFIX_PATH='/opt/venv/lib/python3.12/site-packages/torch/share/cmake/Torch'
```

**Side Note:** use `colcon.meta` to avoid repeating the `--cmake-args` every time.
```
cat > ~/sys-arch-2026/colcon.meta << 'EOF'
{
  "names": {
    "vision": {
      "cmake-args": ["-DTorch_DIR=/opt/libtorch/share/cmake/Torch"]
    }
  }
}
EOF
```
Then you can just run `colcon build --packages-select vision` without the extra arguments.

---

Set the library path so the linker can find LibTorch at runtime:

```bash
export LD_LIBRARY_PATH=/opt/libtorch/lib:$LD_LIBRARY_PATH
```

For container on Jetson Nano:
```bash
export LD_LIBRARY_PATH=/opt/venv/lib/python3.12/site-packages/torch/lib:$LD_LIBRARY_PATH
```

---

## camera_feed_node

Opens a V4L2 H264 camera using GStreamer. The stream is split via a `tee`:
- One branch pushes the raw H264 to mediaMTX via `rtspclientsink`
- The other decodes with `nvv4l2decoder` (Jetson hardware) and publishes BGR frames to `/camera/image_raw`

**GStreamer pipeline:**
```
v4l2src device=<device> !
video/x-h264,width=<W>,height=<H>,framerate=<fps>/1 !
h264parse !
tee name=t
  t. ! queue ! rtspclientsink location=<rtsp_url>
  t. ! queue ! nvv4l2decoder ! nvvidconv !
       video/x-raw,format=BGRx !
       appsink name=appsink sync=false max-buffers=1 drop=true
```

**Published topic:** `/camera/image_raw` (`sensor_msgs/msg/Image`, BGR8)

**Parameters:**

| Parameter | Default | Description |
|---|---|---|
| `device` | `/dev/video2` | V4L2 device path |
| `rtsp_url` | `rtsp://localhost:8554/cam` | mediaMTX RTSP push URL |
| `width` | `1920` | Frame width |
| `height` | `1080` | Frame height |
| `fps` | `30` | Camera frame rate |

**Launch:**
```bash
source install/setup.bash
ros2 launch vision camera_feed_node.launch.py \
  device:=/dev/video2 \
  rtsp_url:=rtsp://localhost:8554/cam \
  # need to specify the ros topic it publishes to as well
```

**Monitor:**
```bash
ros2 topic hz /camera/image_raw
```

## keypoint_node

Runs a TorchScript keypoint-detection model on a video file and publishes detections.

**Published topics:**

| Topic | Type | Description |
|---|---|---|
| `/keypoint_detections` | `custom_interfaces/msg/VisionObservations` | Bounding boxes and keypoints |
| `/keypoint_image` | `sensor_msgs/msg/Image` | Annotated frame |

**Parameters:**

| Parameter | Default | Description |
|---|---|---|
| `model_path` | `model.pt` | Path to TorchScript model |
| `video_path` | `video.mp4` | Path to input video file |
| `num_keypoints` | `17` | Keypoints per detection |
| `conf_threshold` | `0.5` | Minimum detection confidence |
| `fps` | `30.0` | Processing rate |

**Launch:**
```bash
source install/setup.bash
ros2 launch vision keypoint_node.launch.py \
  model_path:=/path/to/model.torchscript \
  video_path:=/path/to/video.mp4
```

**Monitor:**
```bash
ros2 topic echo /keypoint_detections
ros2 topic hz /keypoint_detections
```

---

## Testing

Build with tests enabled:

```bash
colcon build --packages-select vision \
  --cmake-args \
    -DBUILD_TESTING=ON \
    -DTorch_DIR=/opt/libtorch/share/cmake/Torch
```

The tests require a TorchScript model and a test image. Set these environment variables before running:

```bash
export VISION_KEYPOINT_MODEL_PATH=/path/to/model.torchscript
export VISION_KEYPOINT_IMAGE_PATH=/path/to/image.jpg
```

Without them the tests will skip rather than fail.

Run the tests:

```bash
colcon test --packages-select vision
colcon test-result --verbose
```

Or run the test binary directly for live output:

```bash
./build/vision/test_keypoint_detector

# Run a specific test
./build/vision/test_keypoint_detector --gtest_filter="*Preprocess*"
```
