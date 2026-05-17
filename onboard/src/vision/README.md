# vision

ROS 2 package containing vision nodes for the robot.

| Node | Description |
|---|---|
| `camera_feed_node` | Ingests a raw H264 camera stream (or a saved video file), forwards live streams to mediaMTX via RTSP, and publishes decoded frames as a ROS image topic |
| `keypoint_node` | Subscribes to two synchronized camera topics, runs a keypoint-detection model on each frame, and publishes detections and (annotated) images as a `VisionResult` |

---

## Quick start

Launch both cameras and the keypoint detector in one command:

```bash
source install/setup.bash
ros2 launch vision vision.launch.py model_path:=/path/to/model.engine
```

All other parameters have defaults. Override as needed:

```bash
ros2 launch vision vision.launch.py \
  model_path:=/path/to/model.engine \
  device_left:=/dev/video6 \
  device_right:=/dev/video2 \
  annotate_images:=true
```

| Parameter | Default | Description |
|---|---|---|
| `model_path` | *(required)* | Path to TensorRT engine |
| `device_left` | `/dev/video6` | Left camera V4L2 device |
| `device_right` | `/dev/video2` | Right camera V4L2 device |
| `rtsp_url_left` | `rtsp://localhost:8554/left` | mediaMTX RTSP push URL for left camera |
| `rtsp_url_right` | `rtsp://localhost:8554/right` | mediaMTX RTSP push URL for right camera |
| `width` | `1920` | Frame width (both cameras) |
| `height` | `1080` | Frame height (both cameras) |
| `fps` | `30` | Frame rate (both cameras) |
| `num_keypoints` | `4` | Keypoints per detection |
| `conf_threshold` | `0.2` | Minimum detection confidence |
| `annotate_images` | `false` | Draw bounding boxes and keypoints on published images |

---

## camera_feed_node

Supports two input modes selected automatically from the `device` parameter:

### Camera mode (default)

Opens a V4L2 H264 camera using GStreamer. The stream is split via a `tee`:
- One branch pushes the raw H264 to mediaMTX via `rtspclientsink`
- The other decodes with `nvv4l2decoder` (Jetson hardware) and publishes BGR frames to the ROS topic

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

### Video file mode

When `device` ends with a recognised video extension (`.mp4 .avi .mkv .mov .webm .m4v .flv .wmv`), the node skips GStreamer and reads the file with OpenCV `VideoCapture`. Frames are published at the file's native FPS (falls back to the `fps` parameter if the file reports none). The node stops cleanly when the file ends. `rtsp_url`, `width`, and `height` are ignored in this mode.

**Published topic:** Configurable via the `topic` parameter (`sensor_msgs/msg/Image`, BGR8)

**Parameters:**

| Parameter | Default | Description |
|---|---|---|
| `device` | `/dev/video2` | V4L2 device path **or** path to a video file |
| `rtsp_url` | `rtsp://localhost:8554/cam` | mediaMTX RTSP push URL (camera mode only) |
| `topic` | `camera/image_raw` | ROS topic to publish frames on |
| `width` | `1920` | Frame width (camera mode only) |
| `height` | `1080` | Frame height (camera mode only) |
| `fps` | `30` | Camera frame rate / fallback FPS for video files |

**Launch (camera):**
```bash
source install/setup.bash
ros2 launch vision camera_feed_node.launch.py \
  device:=/dev/video2 \
  rtsp_url:=rtsp://localhost:8554/cam \
  topic:=camera/image_raw
```

**Launch (video file):**
```bash
source install/setup.bash
ros2 launch vision camera_feed_node.launch.py \
  device:=/path/to/recording.mp4 \
  topic:=camera/image_raw
```

**Monitor:**
```bash
ros2 topic hz /camera/image_raw  # adjust to match your topic parameter
```

## keypoint_node

Subscribes to two synchronized camera topics, runs a TorchScript keypoint-detection model on each frame, and publishes the results as a single `VisionResult` message.

**Subscribed topics:**

| Topic | Type | Description |
|---|---|---|
| `<image_topic_left>` | `sensor_msgs/msg/Image` | Left camera feed (configurable) |
| `<image_topic_right>` | `sensor_msgs/msg/Image` | Right camera feed (configurable) |

The two topics are synchronized using `message_filters::ApproximateTime`.

**Published topics:**

| Topic | Type | Description |
|---|---|---|
| `keypoint_result` | `custom_interfaces/msg/VisionResult` | Detections and frames for both cameras |
| `keypoint_image_left` | `sensor_msgs/msg/Image` | Left camera frame (annotated if `annotate_images` is true) |
| `keypoint_image_right` | `sensor_msgs/msg/Image` | Right camera frame (annotated if `annotate_images` is true) |

**Parameters:**

| Parameter | Default | Description |
|---|---|---|
| `model_path` | `model.engine` | Path to serialized TensorRT engine |
| `num_keypoints` | `4` | Keypoints per detection |
| `conf_threshold` | `0.5` | Minimum detection confidence |
| `image_topic_left` | `/camera/left/image_raw` | Left camera image topic |
| `image_topic_right` | `/camera/right/image_raw` | Right camera image topic |
| `annotate_images` | `false` | Draw bounding boxes and keypoints on published images |

**Launch:**
```bash
source install/setup.bash
ros2 launch vision keypoint_node.launch.py \
  model_path:=/path/to/model.engine \
  image_topic_left:=/camera/left/image_raw \
  image_topic_right:=/camera/right/image_raw
```

**Visualize in RViz:**
```bash
rviz2
```
Click "Add" > "By topic" > select `keypoint_image_left` or `keypoint_image_right` > Image.

---

## Testing

Build with tests enabled:

```bash
colcon build --packages-select vision --cmake-args -DBUILD_TESTING=ON
```

The tests require a TensorRT engine and a test image. Set these environment variables before running:

```bash
export VISION_KEYPOINT_MODEL_PATH=/path/to/model.engine
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
