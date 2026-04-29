# Vision
Wiki [notion page](https://www.notion.so/crsucd/Vision-2a98a3eca2f080979dfbdb59448b942f)
## Camera Streaming & Recording
Check out the [Simultaneous Stream and Recording Guide](./Simultaneous_Stream_and_Recording.md).
## ML Related
See [`machine_learning`](./machine_learning) dir
## Architecture
Check out our [current plan](./Architecture.md) for how the vision system will work. 
## Keypoint detector node
Readme [here](../onboard/src/vision/README.md)
### TODO for onboard/src/vision package:
- [x] Add two more camera feed publisher nodes
    - [ ] Need a node to filter listen on both topics and filter out of the sync ones. 
    - [ ] Make the keypoint detector node read from a camera feed topic instead of a video file
    - [x] update the (web page)[../remote_control_webpage] to show stereo camera feeds
- [x] Use a custom message type for keypoint results instead of a string
- [ ] Switch to use `.engine` instead of `.torchscript` for *speed*
    - [ ] fix up docker for jetson 
