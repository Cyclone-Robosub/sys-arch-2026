function [data, info] = result
%Result gives an empty data for custom_interfaces/Result
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/Result';
[data.success, info.success] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
[data.found_object, info.found_object] = ros.internal.ros2.messages.ros2.char('char',16,NaN,0);
[data.reached_waypoint_without_detection, info.reached_waypoint_without_detection] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
info.MessageType = 'custom_interfaces/Result';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,3);
info.MatPath{1} = 'success';
info.MatPath{2} = 'found_object';
info.MatPath{3} = 'reached_waypoint_without_detection';
