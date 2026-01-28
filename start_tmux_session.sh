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

# Create new detached tmux session
tmux new-session -d -s $SESSION

# --- Thrust Interface ---
tmux split-window -h -t $SESSION
tmux send-keys -t $SESSION:0.0 'source install/setup.sh' C-m
tmux send-keys -t $SESSION:0.0 'ros2 run thrust_interface thrust_interface' C-m

# --- Software Multiplexer ---
tmux send-keys -t $SESSION:0.1 'source install/setup.sh' C-m
tmux send-keys -t $SESSION:0.1 'ros2 run soft_mux soft_mux' C-m

# --- System Monitor (btop) ---
tmux split-window -v -t $SESSION:0.1
tmux send-keys -t $SESSION:0.2 'btop' C-m

# --- Mux Controller ---
tmux split-window -v -t $SESSION:0.0
tmux send-keys -t $SESSION:0.1 'source install/setup.sh' C-m
tmux send-keys -t $SESSION:0.1 'ros2 run mux_controller mux_controller' C-m

################################################################################
# SECTION 2: (Optional) Video Streaming and Recording Window
################################################################################

tmux new-window -t $SESSION

# --- mediaMTK ---
tmux send-keys -t $SESSION:1 'cd ~/mediaMTK && ./mediamtk' C-m

# --- ffmpeg ---
tmux split-window -h -t $SESSION:1
tmux send-keys -t $SESSION:1.1 \
    'ffmpeg -f v4l2 -input_format h264 -video_size 1920x1080 -framerate 30 \
    -fflags +genpts \
    -i /dev/video2 \
    -c:v copy -f rtsp rtsp://localhost:8554/cam \
    -c:v copy -avoid_negative_ts make_zero -f mp4 ~/recordings/output_$(date +%Y%m%d_%H%M%S).mp4' C-m

################################################################################
# Attach to Session
################################################################################

# Bring the configured tmux session to the foreground
tmux attach -t $SESSION