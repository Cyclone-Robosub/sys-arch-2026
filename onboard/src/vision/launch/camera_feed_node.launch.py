from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            'device',
            default_value='/dev/video2',
            description='V4L2 camera device path, or path to a video file (.mp4 .avi .mkv .mov .webm .m4v .flv .wmv)'
        ),
        DeclareLaunchArgument(
            'rtsp_url',
            default_value='rtsp://localhost:8554/cam',
            description='RTSP URL of the mediaMTX server to push the stream to'
        ),
        DeclareLaunchArgument(
            'topic',
            default_value='camera/image_raw',
            description='ROS topic to publish the camera feed on'
        ),
        DeclareLaunchArgument(
            'width',
            default_value='1920',
            description='Frame width in pixels'
        ),
        DeclareLaunchArgument(
            'height',
            default_value='1080',
            description='Frame height in pixels'
        ),
        DeclareLaunchArgument(
            'fps',
            default_value='30',
            description='Camera frame rate'
        ),

        Node(
            package='vision',
            executable='camera_feed_node',
            name='camera_feed_node',
            parameters=[{
                'device':   LaunchConfiguration('device'),
                'rtsp_url': LaunchConfiguration('rtsp_url'),
                'width':    LaunchConfiguration('width'),
                'height':   LaunchConfiguration('height'),
                'fps':      LaunchConfiguration('fps'),
                'topic':    LaunchConfiguration('topic'),
            }],
            output='screen',
        ),
    ])
