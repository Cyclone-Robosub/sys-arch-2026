function [data, info] = waypointMask
%WaypointMask gives an empty data for custom_interfaces/WaypointMask
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/WaypointMask';
[data.x, info.x] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
[data.y, info.y] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
[data.z, info.z] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
[data.roll, info.roll] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
[data.pitch, info.pitch] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
[data.yaw, info.yaw] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
info.MessageType = 'custom_interfaces/WaypointMask';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,6);
info.MatPath{1} = 'x';
info.MatPath{2} = 'y';
info.MatPath{3} = 'z';
info.MatPath{4} = 'roll';
info.MatPath{5} = 'pitch';
info.MatPath{6} = 'yaw';
