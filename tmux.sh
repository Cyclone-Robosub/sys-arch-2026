#!/bin/bash

# This script sets up a tmux session 

SESSION="manny"

# start a new tmux session named "manny" in detached mode
tmux new-session -d -s $SESSION

# set up the first pane running thrust interface
tmux split-window -h -t $SESSION # split the window horizontally
tmux send-keys -t $SESSION:0.0 'source install/setup.sh' C-m
tmux send-keys -t $SESSION:0.0 'ros2 run thrust_interface thrust_interface' C-m

# set up the second pane running mux
tmux send-keys -t $SESSION:0.1 'source install/setup.sh' C-m
tmux send-keys -t $SESSION:0.1 'ros2 run soft_mux soft_mux' C-m

# Bring the tmux session to the foreground
tmux attach -t $SESSION