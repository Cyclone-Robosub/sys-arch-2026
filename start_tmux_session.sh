#!/bin/bash

################################################################################
# RoboSub System Startup Script
################################################################################
# Purpose: Start all components using one script
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

VISION="false"
BRAIN_CONTAINER="manny_brain"
SESSION="manny"

# 1. SAVE ORIGINAL ARGS BEFORE SHIFTING
ORIG_ARGS=("$@")

# Parse command-line flags until no arguments remain.
while [[ $# -gt 0 ]]; do
	case "$1" in
		--vision)
			VISION="true"
			shift
			;;
		--help|-h)
			cat <<'EOF' 
Usage: ./start_tmux_session.sh [options]

Options:
	--vision    Run the vision components inside a separate container (manny_brain)
	--help, -h  Show this help message
EOF
			exit 0
			;;
		*)
			echo "Unknown option: $1" >&2
			echo "Run with --help to see available options." >&2
			exit 1
			;;
	esac
done

# 2. DISTROBOX RE-ENTRY (Fixed Argument Passing & Clean Exit)
if [[ ! -f /opt/ros/jazzy/setup.bash ]]; then
	echo "ROS not found. Attempting to re-run in distrobox container..."
	distrobox enter ubuntu-ros -- "$0" "${ORIG_ARGS[@]}"
	# Exit distrobox with tmux
	exit 0
fi

if [[ "$VISION" == "true" ]]; then
	distrobox-host-exec docker compose up --detach
	echo "Waiting for $BRAIN_CONTAINER to be ready..."
	until distrobox-host-exec docker compose exec "$BRAIN_CONTAINER" test -f install/setup.sh 2>/dev/null; do
		sleep 1
	done
	echo "$BRAIN_CONTAINER is ready."
fi

# Source workspace
if [[ -f install/setup.sh ]]; then
	source install/setup.sh
else
	echo "Warning: install/setup.sh not found. Make sure you are in the workspace root."
fi

################################################################################
# SECTION 1: Main Window - Core System Components
################################################################################

# --- Thrust Interface ---
THRUST_INTERFACE_PANE=$(tmux new-session -d -s "$SESSION" -P -F "#{pane_id}" "ros2 run thrust_interface thrust_interface; bash" )

# --- Software Multiplexer ---
SOFT_MUX_PANE=$(tmux split-window -h -t "$THRUST_INTERFACE_PANE" -P -F "#{pane_id}" "ros2 run soft_mux soft_mux; bash" )

# --- System Monitor (btop) ---
tmux split-window -v -t "$SOFT_MUX_PANE" "btop; bash"

# --- Mux Controller ---
tmux split-window -v -t "$THRUST_INTERFACE_PANE" "ros2 run mux_controller mux_controller; bash"

################################################################################
# SECTION 2: Video Streaming and Recording Window
################################################################################

if [[ "$VISION" == "true" ]]; then
	# --- mediaMTX ---
	MEDIAMTX_PANE=$(tmux new-window -t "$SESSION" -P -F "#{pane_id}" "cd ~/mediaMTX && ./mediamtx; bash")

	# --- camera_feed_node (cam 1) ---
	CAM1_PANE=$(tmux split-window -h -t "$MEDIAMTX_PANE" -P -F "#{pane_id}" "distrobox-host-exec docker compose exec $BRAIN_CONTAINER bash -ic 'source install/setup.sh && ros2 launch vision camera_feed_node.launch.py device:=/dev/video2 rtsp_url:=rtsp://localhost:8554/left topic:=/cameras/left; exec bash'")

	# --- camera_feed_node (cam 2) ---
	tmux split-window -v -t "$CAM1_PANE" "distrobox-host-exec docker compose exec $BRAIN_CONTAINER bash -ic 'source install/setup.sh && ros2 launch vision camera_feed_node.launch.py device:=/dev/video6 rtsp_url:=rtsp://localhost:8554/right topic:=/cameras/right; exec bash'"
fi

################################################################################
# SECTION 3: Additional Components: IMU
################################################################################

# --- IMU Node ---
SENSOR_PANE=$(tmux new-window -t "$SESSION" -P -F "#{pane_id}" "ros2 run inertial_sense_ros2 inertial_sense_ros2_node; bash")

# --- DVL Node ---
tmux split-window -v -t "$SENSOR_PANE" "ros2 run dvl dvl; bash"

################################################################################
# SECTION 4: Additional Components: CLI
################################################################################

CLI_PANE=$(tmux new-window -t "$SESSION" -P -F "#{pane_id}" "ros2 run pwm_cli pwm_cli_node; bash")

################################################################################
# SECTION 5: Remote Control Webpage
################################################################################

# --- Ros Bridge ---
ROSBRIDGE_PANE=$(tmux new-window -t "$SESSION" -P -F "#{pane_id}" "ros2 launch rosbridge_server rosbridge_websocket_launch.xml; bash")

# --- Remote Control Webpage Server ---
tmux split-window -v -t "$ROSBRIDGE_PANE" "cd ~/sys-arch-2026/remote_control_webpage/build && python3 -m http.server 8080 --bind :: ; bash"

################################################################################
# Attach to Session
################################################################################

# Select the main window
tmux select-window -t "$SESSION:0"

# Bring the configured tmux session to the foreground
tmux attach -t "$SESSION"