import os
from pathlib import Path

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.substitutions import FindPackageShare
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch.substitutions import PathJoinSubstitution
from launch_xml.launch_description_sources import XMLLaunchDescriptionSource


def generate_launch_description() -> LaunchDescription:
    soft_mux_dir = PathJoinSubstitution([FindPackageShare("soft_mux"), "launch"])
    thrust_interface_dir = PathJoinSubstitution(
        [FindPackageShare("thrust_interface"), "launch"]
    )

    robot_name = os.getenv("ROBOT_NAME")

    ld = LaunchDescription()

    ld.add_action(
        IncludeLaunchDescription(
            XMLLaunchDescriptionSource(
                PathJoinSubstitution([soft_mux_dir, "soft_mux_launch.xml"])
            ),
        )
    )

    ld.add_action(
        IncludeLaunchDescription(
            XMLLaunchDescriptionSource(
                PathJoinSubstitution([soft_mux_dir, "thrust_interface_launch.xml"])
            ),
        )
    )

    return ld
