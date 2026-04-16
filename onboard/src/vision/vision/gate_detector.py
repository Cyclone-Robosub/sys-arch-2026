import sys
import rclpy
import json
import config
import argparse
from rclpy.node import Node
from custom_interfaces.msg import VisionObservation, Keypoint, BoundingBox
from rclpy.utilities import remove_ros_args
from ultralytics import YOLO
import cv2 as cv

class GateDetector(Node):
    def __init__(self, model: YOLO, cap: cv.VideoCapture):
        super().__init__('gate_detector')
        self.publisher_ = self.create_publisher(VisionObservation, 'gate_observation', 10)
        self.model = model
        self.cap = cap

    def process_results(self, results) -> None | VisionObservation:
        if len(results) == 0 or len(results[0].keypoints) == 0:
            return None
        observation = VisionObservation()
        observation.num_keypoints_per_object = config.NUM_KEYPOINTS
        observation.category = config.CATEGORY

        flat_keypoints = []
        flat_keypoints_confidences = []

        # YOLO results is usually a list; we iterate through it
        for result in results:
        
            # --- Handle Bounding Boxes ---
            for box in result.boxes.cpu():
                b = BoundingBox()
                # Unpack xywh and convert to native floats in one go
                b.x, b.y, b.w, b.h = box.xywhn.squeeze().tolist()
                b.confidence = box.conf.item()
                
                observation.bounding_box.append(b)
            
        # --- Handle Keypoints ---
            flat_keypoints.extend(
                result.keypoints.xyn.cpu().flatten().tolist()
            )
            flat_keypoints_confidences.extend(
                result.keypoints.conf.cpu().flatten().tolist()
            )
            
        for i in range(0, len(flat_keypoints), 2):
            kpt = Keypoint()
            kpt.x = flat_keypoints[i]
            kpt.y = flat_keypoints[i + 1]
            kpt.confidence = flat_keypoints_confidences[i // 2]
            observation.keypoints.append(kpt)

                

    def run(self):
        ok, frame = self.cap.read()
        if not ok:
            self.get_logger().error("Can't receive frame (stream end?). Exiting ...")
            raise RuntimeError("Can't receive frame (stream end?). Exiting ...")
        rgb_frame = cv.cvtColor(frame, cv.COLOR_BGR2RGB)
        results = self.model.predict(rgb_frame, conf=config.CONFIDENCE_THRESHOLD)
        results = self.process_results(results)
        if results is None:
            self.get_logger().info("No keypoints detected")
            return
        return results


def main(args=None):
    rclpy.init(args=args)

    parser = argparse.ArgumentParser(description="Run the gate detector node")
    parser.add_argument(
        "-m", "--model_path", type=str, 
        default=config.MODEL_PATH, 
        help="Path to the YOLO model checkpoint"
    )
    args = parser.parse_args(remove_ros_args(args=sys.argv)[1:])

    node = GateDetector()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
