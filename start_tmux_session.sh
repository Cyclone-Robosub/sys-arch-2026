#!/bin/bash

################################################################################
# RoboSub System Startup Script
################################################################################
# Purpose: Start all component using one script
# Usage: Creates a tmux session named "manny" 
#
# Layout Overview:
#   Window 0 (Main):
#     ┌─────────────────┬─────────────────┐
#     │  thrust_        │  soft_mux       │
#     │  interface      │                 │
#     ├─────────────────┤─────────────────┤
#     │  mux_controller │  btop (monitor) │
#     └─────────────────┴─────────────────┘
################################################################################

if [[ ! -f /opt/ros/jazzy/setup.bash ]]; then
	echo "ROS not found. Attempting to re-run in distrobox container..."
	distrobox enter ubuntu-ros -- $0 # Run this script, now in container
	distrobox enter ubuntu-ros # After finished, stay in the container
	exit # Don't run the script again after we're done
fi

source install/setup.sh
source ~/.$(echo $SHELL | awk -F  '/' '{print $NF}')rc

SESSION="manny"

################################################################################
# SECTION 1: Main Window - Core System Components
################################################################################

# --- Thrust Interface ---
# Create new detached tmux session
THRUST_INTERFACE_PANE=$(tmux new-session -d -s $SESSION -P -F "#{pane_id}" "ros2 run thrust_interface thrust_interface; bash" )

# --- Software Multiplexer ---
SOFT_MUX_PANE=$(tmux split-window -h -t $THRUST_INTERFACE_PANE -P -F "#{pane_id}" "ros2 run soft_mux soft_mux; bash" )

# --- System Monitor (btop) ---
tmux split-window -v -t $SOFT_MUX_PANE "btop; bash"

# --- Mux Controller ---
tmux split-window -v -t $THRUST_INTERFACE_PANE "ros2 run mux_controller mux_controller; bash"

################################################################################
# SECTION 2: Video Streaming and Recording Window
################################################################################

# --- mediaMTX ---
# Create new window 
MEDIAMTX_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "mediamtx; bash")

# --- ffmpeg ---
FFMPEG_PANE=$(tmux split-window -h -t $MEDIAMTX_PANE -P -F "#{pane_id}" "ffmpeg -f v4l2 -input_format h264 -video_size 1920x1080 -framerate 30 \
	-fflags +genpts \
	-i /dev/video2 \
	-c:v copy -f rtsp rtsp://localhost:8554/down \
	-c:v copy -avoid_negative_ts make_zero -f mp4 ~/Robosub/recordings/output_$(date +%Y%m%d_%H%M%S)_bottom.mp4; bash") 

tmux split-window -v -t $FFMPEG_PANE "ffmpeg -f v4l2 -input_format h264 -video_size 1920x1080 -framerate 30 \
	-fflags +genpts \
	-i /dev/video6 \
	-c:v copy -f rtsp rtsp://localhost:8554/front \
	-c:v copy -avoid_negative_ts make_zero -f mp4 ~/Robosub/recordings/output_$(date +%Y%m%d_%H%M%S)_front.mp4; bash"

################################################################################
# SECTION 3: Additional Components: Sensors
################################################################################

# --- IMU Node ---
SENSOR_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "ros2 run inertial_sense_ros2 inertial_sense_ros2_node; bash")

# --- DVL Node ---
DVL_PANE=$(tmux split-window -v -t $SENSOR_PANE -P -F "#{pane_id}" "ros2 run dvl dvl; bash")

# --- Data Logger ---
tmux split-window -h -t $DVL_PANE "ros2 run data_logger data_logger; bash"

################################################################################
# SECTION 4: Additional Components: CLI
################################################################################

CLI_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "ros2 run pwm_cli pwm_cli_node; bash")

################################################################################
# Attach to Session
################################################################################

# Select the main window
tmux select-window -t $SESSION:0

# Bring the configured tmux session to the foreground
tmux attach -t $SESSION
