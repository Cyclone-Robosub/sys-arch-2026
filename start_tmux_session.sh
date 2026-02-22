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
# SECTION 0: Flag Parsing
################################################################################

USE_CONTAINER=false
BRAIN_CONTAINER="manny_brain"
VISION_CONTAINER="manny_vision"

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

################################################################################
# SECTION 1: Main Window - Core System Components
################################################################################

# --- Thrust Interface ---
# Create new detached tmux session
if [[ "$USE_CONTAINER" == true ]]; then
	THRUST_INTERFACE_PANE=$(tmux new-session -d -s $SESSION -P -F "#{pane_id}" "docker compose exec $BRAIN_CONTAINER bash -ic 'ros2 run thrust_interface thrust_interface'; bash" )
else 
    THRUST_INTERFACE_PANE=$(tmux new-session -d -s $SESSION -P -F "#{pane_id}" "source install/setup.sh && ros2 run thrust_interface thrust_interface; bash" )
fi


# --- Software Multiplexer ---
if [[ "$USE_CONTAINER" == true ]]; then
	SOFT_MUX_PANE=$(tmux split-window -h -t $THRUST_INTERFACE_PANE -P -F "#{pane_id}" "docker compose exec $BRAIN_CONTAINER bash -ic 'ros2 run soft_mux soft_mux'; bash" )
else
	SOFT_MUX_PANE=$(tmux split-window -h -t $THRUST_INTERFACE_PANE -P -F "#{pane_id}" "source install/setup.sh && ros2 run soft_mux soft_mux; bash" )
fi

# --- System Monitor (btop) ---
tmux split-window -v -t $SOFT_MUX_PANE "btop; bash"

# --- Mux Controller ---
if [[ "$USE_CONTAINER" == true ]]; then
    tmux split-window -v -t $THRUST_INTERFACE_PANE "docker compose exec $BRAIN_CONTAINER bash -ic 'ros2 run mux_controller mux_controller'; bash" 
else
    tmux split-window -v -t $THRUST_INTERFACE_PANE "source install/setup.sh && ros2 run mux_controller mux_controller; bash"
fi

################################################################################
# SECTION 2: (Optional) Video Streaming and Recording Window
################################################################################

# --- mediaMTX ---
# Create new window 
MEDIAMTX_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "cd ~/mediaMTX && ./mediamtx; bash")

# --- ffmpeg ---
if [[ "$USE_CONTAINER" == true ]]; then
# need to fix this
    tmux split-window -h -t $MEDIAMTX_PANE "docker compose exec $VISION_CONTAINER bash -ic 'ffmpeg -f v4l2 -input_format h264 \ 
        -video_size 1920x1080 -framerate 30 \
        -fflags +genpts \
        -i /dev/video2 \
        -c:v copy -f rtsp rtsp://localhost:8554/cam; bash'" 
else
    tmux split-window -h -t $MEDIAMTX_PANE "ffmpeg -f v4l2 -input_format h264 \
        -video_size 1920x1080 -framerate 30 \
        -fflags +genpts \
        -i /dev/video2 \
        -c:v copy -f rtsp rtsp://localhost:8554/cam \
        -c:v copy -avoid_negative_ts make_zero -f mp4 ~/recordings/output_$(date +%Y%m%d_%H%M%S).mp4; bash" # Record 
fi

################################################################################
# SECTION 3: (Optional)  IMU
################################################################################

# --- IMU Node ---
# if [[ "$USE_CONTAINER" == true ]]; then
# 	tmux new-window -t $SESSION "docker compose exec $BRAIN_CONTAINER bash -ic 'ros2 run inertial_sense_ros2 inertial_sense_ros2_node'" 
# else
# 	tmux new-window -t $SESSION "source install/setup.sh && ros2 run inertial_sense_ros2 inertial_sense_ros2_node; bash"
# fi

################################################################################
# SECTION 4: (Optional) Joystick controller
################################################################################

if [[ "$USE_CONTAINER" == true ]]; then
	JOYSTICK_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "docker compose exec $BRAIN_CONTAINER bash -ic 'ros2 run simple_joystick_controller Simple_Joystick_Controller'; bash")
else
	JOYSTICK_PANE=$(tmux new-window -t $SESSION -P -F "#{pane_id}" "source install/setup.sh && ros2 run simple_joystick_controller Simple_Joystick_Controller; bash")
fi

tmux split-window -v -t $JOYSTICK_PANE "cd ~/sys-arch-2026/remote_control_webpage && python3 -m http.server 8000; bash"

################################################################################
# Attach to Session
################################################################################

# Select the main window
tmux select-window -t $SESSION:0

# Bring the configured tmux session to the foreground
tmux attach -t $SESSION