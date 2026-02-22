from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.substitutions import PathJoinSubstitution
from launch_xml.launch_description_sources import XMLLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    rosbridge_dir = PathJoinSubstitution(
        [FindPackageShare("rosbridge_server"), "launch"]
    )
    mux_controller_dir = PathJoinSubstitution(
        [FindPackageShare("mux_controller"), "launch"]
    )
    joystick_controller_dir = PathJoinSubstitution(
        [FindPackageShare("simple_joystick_controller"), "launch"]
    )
    return LaunchDescription(
        [
            IncludeLaunchDescription(
                XMLLaunchDescriptionSource(
                    PathJoinSubstitution(
                        [rosbridge_dir, "rosbridge_websocket_launch.xml"]
                    )
                )
            ),
            IncludeLaunchDescription(
                XMLLaunchDescriptionSource(
                    PathJoinSubstitution(
                        [mux_controller_dir, "mux_controller_launch.xml"]
                    )
                )
            ),
            IncludeLaunchDescription(
                XMLLaunchDescriptionSource(
                    PathJoinSubstitution(
                        [
                            joystick_controller_dir, "joystick_controller_launch.xml"
                        ]
                    )
                )
            ),
        ]
    )
