# Vision
Wiki [notion page](https://www.notion.so/crsucd/Vision-2a98a3eca2f080979dfbdb59448b942f)

# Monocular Camera Calibration & 6-DoF Pose Estimation

Code to implement a monocular camera calibration and 6-DoF pose estimation using OpenCV.

Initial implementation to estimate the 3D position and orientation of a planar ArUco marker relative to the camera using `solvePnP`. All translation outputs are expressed in metric units (meters).

Checkerboard Calibration  
→ Intrinsics (K, distortion coefficients)  
→ ArUco Detection  
→ Perspective-n-Point (PnP)  
→ Reprojection Validation  

The pose estimation follows the pinhole camera model:

    u = K [R | t] X

Where:
- K is the intrinsic matrix
- R, t are rotation and translation from object frame to camera frame
- X is a 3D point on the marker
- u is its corresponding 2D pixel location

## Camera Coordinate Frame

OpenCV convention:

- x → right  
- y → down  
- z → forward (along optical axis)

The translation vector `tvec` represents the position of the marker **center** in the camera coordinate frame.

## Pose Estimation

1. Generate marker:

    python aruco_gen.py

2. Measure the side length of the **black square only** (in meters).
3. Set `marker_length` in `pose_est.py`.
4. Run:

    python pose_est.py

The system will:
- Detect the marker
- Estimate pose (rvec, tvec)
- Draw coordinate axes
- Compute per-frame reprojection error

Mean reprojection error < 1 pixel indicates good calibration quality.
