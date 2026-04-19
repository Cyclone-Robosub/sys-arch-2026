import cv2
import argparse
import sys

try:
    if sys.argv[1] == '--record':
        fourcc = cv2.VideoWriter_fourcc(*'mp4v')
        out1 = cv2.VideoWriter('output1.mp4', fourcc, 30.0, (640, 480))
        out2 = cv2.VideoWriter('output2.mp4', fourcc, 30.0, (640, 480))
except IndexError:
    print("No recording option provided. Running in display mode.")

cap_l = cv2.VideoCapture(0)
cap_r = cv2.VideoCapture(2)

def get_synced_frames(tol=0.01):
    """
    Attempts to grab frames from both cameras. 
    tol - the tolerance in seconds
    """
    
    ret_l, frame_l = cap_l.read()
    ts_l = cap_l.get(cv2.CAP_PROP_POS_MSEC)
    
    ret_r, frame_r = cap_r.read()
    ts_r = cap_r.get(cv2.CAP_PROP_POS_MSEC)

    diff = abs(ts_l - ts_r)
    
    if diff <= tol:
        return True, frame_l, 1, ts_l
    else:
        return False, frame_l, frame_r, ts_l

while True:
    in_sync, img_l, img_r, ts = get_synced_frames()
    
    if in_sync:
        cv2.imshow("Synced Left", img_l)
        cv2.imshow("Synced Right", img_r)
        if sys.argv[1] == '--record':
            out1.write(img_l)
            out2.write(img_r)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap_l.release()
cap_r.release()
if sys.argv[1] == '--record':
    out1.release()
    out2.release()
cv2.destroyAllWindows()