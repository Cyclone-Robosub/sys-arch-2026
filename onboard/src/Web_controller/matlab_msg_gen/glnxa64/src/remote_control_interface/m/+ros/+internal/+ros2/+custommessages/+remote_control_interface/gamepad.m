function [data, info] = gamepad
%Gamepad gives an empty data for remote_control_interface/Gamepad
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'remote_control_interface/Gamepad';
[data.x, info.x] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
[data.y, info.y] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
[data.rise, info.rise] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
[data.sink, info.sink] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
[data.yaw, info.yaw] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
[data.pitch, info.pitch] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
info.MessageType = 'remote_control_interface/Gamepad';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,6);
info.MatPath{1} = 'x';
info.MatPath{2} = 'y';
info.MatPath{3} = 'rise';
info.MatPath{4} = 'sink';
info.MatPath{5} = 'yaw';
info.MatPath{6} = 'pitch';
