% Create the ROS 2 node
node = ros2node("/matlab_listener");

% Subscribe to the topic using your custom type
sub = ros2subscriber(node, "/gate_bounding_box", "custom_interfaces/BoundingBox");

% Wait for the next message and display it
disp("Waiting for message...");
[box, status] = receive(sub, 5); % 5-second timeout

if status
    fprintf("x: %.2f", box.x)
else
    disp("Timed out!")
end