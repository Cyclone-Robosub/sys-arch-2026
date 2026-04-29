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

source install/setup.sh

SESSION="manny"

################################################################################
# SECTION 0: Flag Parsing
################################################################################

USE_CONTAINER=false
BRAIN_CONTAINER="manny_brain"

# Parse command-line flags until no arguments remain.
while [[ $# -gt 0 ]]; do
	# Match on the current argument.
	case "$1" in
		--container)
			# Remember that the container mode was requested.
			USE_CONTAINER=true
			# Consume this flag and move to the next argument.
			shift
			;; # End of this case branch.
		--help|-h)
			# Print usage and exit cleanly.
			cat <<'EOF' 
Usage: ./start_tmux_session.sh [options]

Options:
	--container    Run the components inside container
	--help, -h     Show this help message
EOF
			exit 0
			;;
		*)
			# Unknown flag: report error and stop.
			echo "Unknown option: $1" >&2
			echo "Run with --help to see available options." >&2
			exit 1
			;;
	esac
done

if [[ "$USE_CONTAINER" == true ]]; then
	echo "Running components inside container..."
fi

ros2_cmd() {
    local pkg="$1" node="$2"
    if [[ "$USE_CONTAINER" == true ]]; then
        echo "docker compose exec $BRAIN_CONTAINER bash -ic 'source install/setup.sh && ros2 run $pkg $node; exec bash'"
    else
        echo "source install/setup.sh && ros2 run $pkg $node; bash"
    fi
}

################################################################################
# SECTION 1: Main Window - Core System Components
################################################################################

# --- Thrust Interface ---
THRUST_INTERFACE_PANE=$(tmux new-session -d -s $SESSION -P -F "#{pane_id}" "$(ros2_cmd thrust_interface thrust_interface)")

# --- Software Multiplexer ---
SOFT_MUX_PANE=$(tmux split-window -h -t $THRUST_INTERFACE_PANE -P -F "#{pane_id}" "$(ros2_cmd soft_mux soft_mux)")

# --- System Monitor (btop) ---
tmux split-window -v -t $SOFT_MUX_PANE "btop; bash"

# --- Mux Controller ---
tmux split-window -v -t $THRUST_INTERFACE_PANE "$(ros2_cmd mux_controller mux_controller)"

################################################################################
# SECTION 2: Video Streaming and Recording Window
################################################################################

# --- mediaMTX ---
# Create new window 
MEDIAMTX_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "cd ~/mediaMTX && ./mediamtx; bash")

# --- camera_feed_node (cam 1) ---
if [[ "$USE_CONTAINER" == true ]]; then
    CAM1_PANE=$(tmux split-window -h -t $MEDIAMTX_PANE -P -F "#{pane_id}" "docker compose exec $BRAIN_CONTAINER bash -ic 'source install/setup.sh && ros2 launch vision camera_feed_node.launch.py device:=/dev/video2 rtsp_url:=rtsp://localhost:8554/left topic:=/cameras/left; exec bash'")

# --- camera_feed_node (cam 2) ---
    tmux split-window -v -t $CAM1_PANE "docker compose exec $BRAIN_CONTAINER bash -ic 'source install/setup.sh && ros2 launch vision camera_feed_node.launch.py device:=/dev/video6 rtsp_url:=rtsp://localhost:8554/right topic:=/cameras/right; exec bash'"

else
	tmux split-window -h -t $MEDIAMTX_PANE "ffmpeg -f v4l2 -input_format h264 \
        -video_size 1920x1080 -framerate 30 \
        -fflags +genpts \
        -i /dev/video2 \
        -c:v copy -f rtsp rtsp://localhost:8554/cam1; bash"
fi

################################################################################
# SECTION 3: (Optional)  IMU
################################################################################

# --- IMU Node ---
if [[ "$USE_CONTAINER" == true ]]; then
	SENSOR_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "docker compose exec $BRAIN_CONTAINER bash -ic 'ros2 run inertial_sense_ros2 inertial_sense_ros2_node'")
else
	SENSOR_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "ros2 run inertial_sense_ros2 inertial_sense_ros2_node; bash")
fi
# --- DVL Node ---
if [[ "$USE_CONTAINER" == true ]]; then
  tmux split-window -v -t $SENSOR_PANE "docker compose exec $BRAIN_CONTAINER bash -ic 'ros2 run dvl dvl'; bash"
else
  tmux split-window -v -t $SENSOR_PANE "ros2 run dvl dvl; bash"
fi

################################################################################
# SECTION 4: (Optional) Joystick controller
################################################################################

# if [[ "$USE_CONTAINER" == true ]]; then
# 	JOYSTICK_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "docker compose exec $BRAIN_CONTAINER bash -ic 'ros2 run simple_joystick_controller Simple_Joystick_Controller'; bash")
# else
# 	JOYSTICK_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "ros2 run simple_joystick_controller Simple_Joystick_Controller; bash")
# fi

################################################################################
# SECTION 5: Additional Components: CLI
################################################################################

JOYSTICK_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "$(ros2_cmd simple_joystick_controller Simple_Joystick_Controller)")

# Starting a simple HTTP server to serve the joystick webpage
tmux split-window -v -t $JOYSTICK_PANE "cd ~/sys-arch-2026/remote_control_webpage/build && python3 -m http.server 8080; bash"

################################################################################
# Attach to Session
################################################################################

# Select the main window
tmux select-window -t $SESSION:0

# Bring the configured tmux session to the foreground
tmux attach -t $SESSION
