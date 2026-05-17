from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        # --- camera args ---
        DeclareLaunchArgument('device_left',    default_value='/dev/video6'),
        DeclareLaunchArgument('device_right',   default_value='/dev/video2'),
        DeclareLaunchArgument('rtsp_url_left',  default_value='rtsp://localhost:8554/left'),
        DeclareLaunchArgument('rtsp_url_right', default_value='rtsp://localhost:8554/right'),
        DeclareLaunchArgument('width',          default_value='1920'),
        DeclareLaunchArgument('height',         default_value='1080'),
        DeclareLaunchArgument('fps',            default_value='30'),

        # --- keypoint args ---
        DeclareLaunchArgument('model_path'),
        DeclareLaunchArgument('num_keypoints',   default_value='4'),
        DeclareLaunchArgument('conf_threshold',  default_value='0.2'),
        DeclareLaunchArgument('annotate_images', default_value='false'),

        Node(
            package='vision',
            executable='camera_feed_node',
            name='camera_feed_left',
            parameters=[{
                'device':   LaunchConfiguration('device_left'),
                'rtsp_url': LaunchConfiguration('rtsp_url_left'),
                'topic':    '/camera/left/image_raw',
                'width':    LaunchConfiguration('width'),
                'height':   LaunchConfiguration('height'),
                'fps':      LaunchConfiguration('fps'),
            }],
            output='screen',
        ),
        Node(
            package='vision',
            executable='camera_feed_node',
            name='camera_feed_right',
            parameters=[{
                'device':   LaunchConfiguration('device_right'),
                'rtsp_url': LaunchConfiguration('rtsp_url_right'),
                'topic':    '/camera/right/image_raw',
                'width':    LaunchConfiguration('width'),
                'height':   LaunchConfiguration('height'),
                'fps':      LaunchConfiguration('fps'),
            }],
            output='screen',
        ),
        Node(
            package='vision',
            executable='keypoint_node',
            name='keypoint_node',
            parameters=[{
                'model_path':        LaunchConfiguration('model_path'),
                'num_keypoints':     LaunchConfiguration('num_keypoints'),
                'conf_threshold':    LaunchConfiguration('conf_threshold'),
                'image_topic_left':  '/camera/left/image_raw',
                'image_topic_right': '/camera/right/image_raw',
                'annotate_images':   LaunchConfiguration('annotate_images'),
            }],
            output='screen',
        ),
    ])
