import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'model_path',
            description='Path to the TorchScript keypoint model'
        ),
        DeclareLaunchArgument(
            'video_path',
            description='Path to the input video file'
        ),
        DeclareLaunchArgument(
            'num_keypoints',
            default_value='4',
            description='Number of keypoints per detection'
        ),
        DeclareLaunchArgument(
            'conf_threshold',
            default_value='0.2',
            description='Minimum confidence score to keep a detection'
        ),
        DeclareLaunchArgument(
            'fps',
            default_value='30.0',
            description='Processing rate in frames per second'
        ),

        Node(
            package='vision',
            executable='keypoint_node',
            name='keypoint_node',
            parameters=[{
                'model_path':     LaunchConfiguration('model_path'),
                'video_path':     LaunchConfiguration('video_path'),
                'num_keypoints':  LaunchConfiguration('num_keypoints'),
                'conf_threshold': LaunchConfiguration('conf_threshold'),
                'fps':            LaunchConfiguration('fps'),
            }],
            output='screen',
        ),
    ])
