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

SESSION="manny"

################################################################################
# SECTION 1: Main Window - Core System Components
################################################################################

# --- Thrust Interface ---
# Create new detached tmux session
THRUST_INTERFACE_PANE=$(tmux new-session -d -s $SESSION -P -F "#{pane_id}" "source install/setup.sh && ros2 run thrust_interface thrust_interface; bash" )

# --- Software Multiplexer ---
SOFT_MUX_PANE=$(tmux split-window -h -t $THRUST_INTERFACE_PANE -P -F "#{pane_id}" "source install/setup.sh && ros2 run soft_mux soft_mux; bash" )

# --- System Monitor (btop) ---
tmux split-window -v -t $SOFT_MUX_PANE "btop; bash"

# --- Mux Controller ---
tmux split-window -v -t $THRUST_INTERFACE_PANE "source install/setup.sh && ros2 run mux_controller mux_controller; bash"

################################################################################
# SECTION 2: (Optional) Video Streaming and Recording Window
################################################################################

# --- mediaMTX ---
# Create new window 
# MEDIAMTX_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "cd ~/mediaMTX && ./mediamtx; bash")

# --- ffmpeg ---
# tmux split-window -h -t $MEDIAMTX_PANE "cd ~/mediaMTX && \
#     ffmpeg -f v4l2 -input_format h264 \
#     -video_size 1920x1080 -framerate 30 \
#     -fflags +genpts \
#     -i /dev/video2 \
#     -c:v copy -f rtsp rtsp://localhost:8554/cam; bash" 

# ################################################################################
# # SECTION 3: (Optional) Additional Components: IMU
# ################################################################################

# --- IMU Node ---
tmux new-window -t $SESSION "source install/setup.sh && ros2 run inertial_sense_ros2 inertial_sense_ros2_node; bash"

# ################################################################################
# # Attach to Session
# ################################################################################

# Select the main window
tmux select-window -t $SESSION:0

# Bring the configured tmux session to the foreground
tmux attach -t $SESSION