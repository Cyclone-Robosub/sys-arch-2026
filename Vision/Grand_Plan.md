## Goals of vision system

- Identify the objects we see and distance vector to each of them
- Speed of the robot
- Depth map of the surrounding field
- Aid navigation algorithm (waypoint following)
- Able to dynamically create and follow waypoints (visually)

### Decomposition

- ML component
    - [Object identification](https://www.notion.so/Gate-Identification-Keypoint-2eb8a3eca2f08070b297dfad31e35cce?pvs=21)
        - Gate (Left right by image of the gate)
            - Gripper objects
            - Any research interest
    - [Keypoint detection](https://www.notion.so/Gate-Identification-Keypoint-2eb8a3eca2f08070b297dfad31e35cce?pvs=21)
        - Non square bounding box
- SLAM component
    - Distance identification
        - [HH/SGBM algo](https://www.notion.so/Research-Vision-Algorithms-2f18a3eca2f0804aac9ae2d4a157d1ff?pvs=21) (likely SGBM)
    - Velocity from derivative
- Stereo vision
    - trigonometry

### Overall flow of data

### Mono camera (for now)

use mermaid for chart

raw image - keypoint model→ keypoints on the object

keypoints + know size of the object → getting the distance and the direction to the object 

### Stereo camera (in future)

1. Stereo
    1. Produce raw images
    2. and depth map with the image
2. ML component
    1. ML component performs Object identification
    2. ML component performs key point identification
    3. Same backbone and different head for keypoints/bounding box
3. SLAM component
    1. SLAM component produces a depth map of the surrounding
    2. use depth map to identify distance to objects

### Current status

- raw image → yolo keypoints → keypoints → post-processing to validate and clean keypoints → algorithm to calculate distance (cv.pnp)  → vector to the keypoints → vector from the center of the gate to the robot.
- stereo vision → under construction
- running on jetson orin nano (8GB of ram)