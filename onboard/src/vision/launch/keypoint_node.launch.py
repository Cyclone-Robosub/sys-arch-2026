from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'model_path',
            description='Path to the serialized TensorRT engine (.engine)'
        ),
        DeclareLaunchArgument(
            'num_keypoints',
            default_value='4',
            description='Number of keypoints per detection'
        ),
        DeclareLaunchArgument(
            'conf_threshold',
            default_value='0.5',
            description='Minimum confidence score to keep a detection'
        ),
        DeclareLaunchArgument(
            'image_topic_left',
            default_value='/camera/left/image_raw',
            description='Left camera image topic'
        ),
        DeclareLaunchArgument(
            'image_topic_right',
            default_value='/camera/right/image_raw',
            description='Right camera image topic'
        ),
        DeclareLaunchArgument(
            'annotate_images',
            default_value='false',
            description='Draw bounding boxes and keypoints on published images'
        ),

        Node(
            package='vision',
            executable='keypoint_node',
            name='keypoint_node',
            parameters=[{
                'model_path':        LaunchConfiguration('model_path'),
                'num_keypoints':     LaunchConfiguration('num_keypoints'),
                'conf_threshold':    LaunchConfiguration('conf_threshold'),
                'image_topic_left':  LaunchConfiguration('image_topic_left'),
                'image_topic_right': LaunchConfiguration('image_topic_right'),
                'annotate_images':   LaunchConfiguration('annotate_images'),
            }],
            output='screen',
        ),
    ])
