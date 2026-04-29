# Vision
Wiki [notion page](https://www.notion.so/crsucd/Vision-2a98a3eca2f080979dfbdb59448b942f)

## Architecture


```mermaid
graph LR
    C1[Camera 1] --> N1[Camera Node 1]
    C2[Camera 2] --> N2[Camera Node 2]

    N1 --> ROS[Filter Node]
    N2 --> ROS

    N1 --> MTX[MediaMTX]
    N2 --> MTX

    MTX --> WEB[Web Page]
```

**Camera Streaming & Recording:**
Check out the [Simultaneous Stream and Recording Guide](./Simultaneous_Stream_and_Recording.md).

**ML models:**
See [`machine_learning`](./machine_learning) dir

### TODO for [`onboard/src/vision`](../onboard/src/vision) package:

- [x] Add two more camera feed publisher nodes
    - [ ] Need a node to filter listen on both topics and filter out of the sync ones. 
        - [ ] Make the keypoint detector node read from a camera feed topic instead of a video file
    - [x] update the (web page)[../remote_control_webpage] to show stereo camera feeds
- [x] Use a custom message type for keypoint results instead of a string
- [ ] Switch to use `.engine` instead of `.torchscript` for *speed*
- [x] fix up docker for jetson 

