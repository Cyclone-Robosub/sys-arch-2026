import cv2
import cv2.aruco as aruco

dictionary = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)

marker_id = 0
marker_size = 600

marker_img = aruco.generateImageMarker(dictionary, marker_id, marker_size)

cv2.imwrite("aruco_marker.png", marker_img)