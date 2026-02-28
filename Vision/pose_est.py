import cv2
import cv2.aruco as aruco
import numpy as np

K = np.load("camera_matrix.npy")
dist = np.load("dist_coeffs.npy")

# side length (m) of the ArUco marker
marker_length = 0.061  # meters

half = marker_length / 2

object_points = np.array([
    [-half,  half, 0],
    [ half,  half, 0],
    [ half, -half, 0],
    [-half, -half, 0]
], dtype=np.float32)

dictionary = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
parameters = aruco.DetectorParameters()

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    corners, ids, _ = aruco.detectMarkers(gray, dictionary, parameters=parameters)

    if ids is not None:
        aruco.drawDetectedMarkers(frame, corners, ids)

        rvecs, tvecs, _ = aruco.estimatePoseSingleMarkers(
            corners,
            marker_length,
            K,
            dist
        )

        # draw red circles at detected corners
        for corner in corners[0][0]:
            cv2.circle(frame, tuple(corner.astype(int)), 4, (0,0,255), -1)

        for rvec, tvec in zip(rvecs, tvecs):
            cv2.drawFrameAxes(frame, K, dist, rvec, tvec, 0.03)

            projected_points, _ = cv2.projectPoints(
                object_points,
                rvec,
                tvec,
                K,
                dist
            )

            projected_points = projected_points.reshape(-1, 2)

            # draw green circles at projected points
            for p in projected_points:
                cv2.circle(frame, tuple(p.astype(int)), 8, (0,255,0), -1)

            error = np.linalg.norm(corners[0][0] - projected_points, axis=1)
            print("Mean reprojection error:", np.mean(error))

            print("Translation (m):", tvec.flatten())

    cv2.imshow("ArUco Pose", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

'''
Tried to detect phone but because of rounded corners, was not able to detect. Will continue working!

import cv2
import numpy as np

# Load calibration
K = np.load("camera_matrix.npy")
dist = np.load("dist_coeffs.npy")

# Phone dimensions (meters)
object_points = np.array([
    [0, 0, 0],
    [0.15, 0, 0],
    [0.15, 0.076, 0],
    [0, 0.076, 0]
], dtype=np.float32)

def order_points(pts):
    rect = np.zeros((4,2), dtype="float32")
    
    s = pts.sum(axis=1)
    rect[0] = pts[np.argmin(s)]  # top-left
    rect[2] = pts[np.argmax(s)]  # bottom-right
    
    diff = np.diff(pts, axis=1)
    rect[1] = pts[np.argmin(diff)]  # top-right
    rect[3] = pts[np.argmax(diff)]  # bottom-left
    
    return rect

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    blur = cv2.GaussianBlur(gray, (5,5), 0)

    edges = cv2.Canny(blur, 50, 150)

    contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area < 2000:
            continue

        peri = cv2.arcLength(cnt, True)
        approx = cv2.approxPolyDP(cnt, 0.02 * peri, True)

        if len(approx) == 4:
            rect = cv2.minAreaRect(cnt)
            box = cv2.boxPoints(rect)
            box = np.int0(box)

            image_points = order_points(box.astype(np.float32))

            success, rvec, tvec = cv2.solvePnP(
                object_points,
                image_points,
                K,
                dist,
                flags=cv2.SOLVEPNP_IPPE
            )

            if success:
                # Reproject
                projected, _ = cv2.projectPoints(
                    object_points,
                    rvec,
                    tvec,
                    K,
                    dist
                )

                projected = projected.reshape(-1,2)

                for p in projected:
                    cv2.circle(frame, tuple(p.astype(int)), 6, (0,255,0), -1)

                # Print translation
                print("Distance (z):", tvec[2][0])

                # Draw contour
                cv2.drawContours(frame, [approx], -1, (255,0,0), 2)

            break

    cv2.imshow("Pose", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
'''