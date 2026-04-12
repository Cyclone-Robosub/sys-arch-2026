import rclpy
import json
from rclpy.node import Node
from custom_interfaces.msg import BoundingBox

class GateDetector(Node):
    def __init__(self):
        super().__init__('gate_detector')
        self.publisher_ = self.create_publisher(BoundingBox, 'gate_bounding_box', 10)
        self.timer = self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        msg = BoundingBox()
        # Set the bounding box coordinates
        msg.x = 0.5
        msg.y = 0.5
        msg.w = 100.5
        msg.h = 100.5
        self.publisher_.publish(msg)

        self.get_logger().info('Published bounding box: x=%d, y=%d, width=%d, height=%d' % (msg.x, msg.y, msg.w, msg.h))

def main():
    rclpy.init()
    node = GateDetector()

    _ = input("Press Enter to start publishing bounding boxes...")
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
