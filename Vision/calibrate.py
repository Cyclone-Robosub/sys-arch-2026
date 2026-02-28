import cv2
import numpy as np
import glob

# Checkerboard dimensions
CHECKERBOARD = (9,6)
square_size = 0.023

# Prepare 3D world points
objp = np.zeros((CHECKERBOARD[0]*CHECKERBOARD[1], 3), np.float32)
objp[:, :2] = np.mgrid[0:CHECKERBOARD[0], 0:CHECKERBOARD[1]].T.reshape(-1, 2)
objp *= square_size

objpoints = []  # 3D real world points
imgpoints = []  # 2D image points

images = glob.glob("calibration_images/*.jpeg")

for fname in images:
    img = cv2.imread(fname)
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    ret, corners = cv2.findChessboardCorners(gray, CHECKERBOARD, None)

    if ret:
        objpoints.append(objp)
        imgpoints.append(corners)

        cv2.drawChessboardCorners(img, CHECKERBOARD, corners, ret)
        cv2.imshow("Corners", img)
        cv2.waitKey(200)

cv2.destroyAllWindows()

ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(
    objpoints, imgpoints, gray.shape[::-1], None, None
)

print("Camera Matrix:\n", mtx)
print("Distortion:\n", dist)

np.save("camera_matrix.npy", mtx)
np.save("dist_coeffs.npy", dist)