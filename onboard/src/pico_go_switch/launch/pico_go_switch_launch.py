from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
   return LaunchDescription([
        Node(
            # name of the package
            package='pico_go_switch',
            # name of the elf
            executable='pico_go_switch',
            # Name of the node
            name="pico_go_switch",
            # Writes to the stdout
            output="screen"
        )
    ])
