# vision

ROS 2 package containing vision nodes for the robot.

| Node | Description |
|---|---|
| `camera_feed_node` | Ingests a raw H264 camera stream (or a saved video file), forwards live streams to mediaMTX via RTSP, and publishes decoded frames as a ROS image topic |

---

## camera_feed_node

Supports two input modes selected automatically from the `device` parameter:

### Camera mode (default)

Opens a V4L2 H264 camera using GStreamer. The stream is split via a `tee`:
- One branch pushes the raw H264 to mediaMTX via `rtspclientsink`
- The other decodes with `avdec_h264` (software) and publishes BGR frames to the ROS topic


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

**Requirements:**

- GStreamer plugins: `gstreamer1.0-libav` (avdec_h264), `gstreamer1.0-plugins-good` (v4l2src), `gstreamer1.0-plugins-bad` (rtspclientsink)
- The camera must expose an H264 stream over V4L2 — verify with `v4l2-ctl --list-formats -d <device>`
- mediaMTX must be running **with a config that defines the target path** (the default `mediamtx.yml` has an `all_others:` catch-all). Launched without a config file, mediaMTX rejects publishes with `400 Bad Request`.

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
ros2 topic hz /camera/image_raw   # adjust to match your topic parameter
ffplay rtsp://localhost:8554/cam  # check the mediaMTX stream
```
