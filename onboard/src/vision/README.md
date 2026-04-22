# vision

ROS 2 package for keypoint detection using a TorchScript model.

## Dependencies

- ROS 2 Jazzy
- LibTorch (C++ API)
- OpenCV

Install ROS dependencies:

```bash
sudo apt install libopencv-dev ros-jazzy-cv-bridge
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

In container on jetson nano:

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

For container on jetson nano:
```bash
export LD_LIBRARY_PATH=/opt/venv/lib/python3.12/site-packages/torch/lib:$LD_LIBRARY_PATH
```

## Running

Source the workspace and launch the node:

```bash
source install/setup.bash
ros2 launch vision keypoint_node.launch.py \
  model_path:=/path/to/model.torchscript \
  video_path:=/path/to/video.mp4
```

Monitor output:

```bash
ros2 topic echo /keypoint_detections
ros2 topic hz /keypoint_detections
```

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
