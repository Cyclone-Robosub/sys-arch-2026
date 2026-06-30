function [data, info] = dropperGoal
%DropperGoal gives an empty data for custom_interfaces/DropperGoal
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/DropperGoal';
[data.dropper_id, info.dropper_id] = ros.internal.ros2.messages.ros2.default_type('uint8',1,0);
[data.timeout, info.timeout] = ros.internal.ros2.messages.ros2.default_type('double',1,0);
info.MessageType = 'custom_interfaces/DropperGoal';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,2);
info.MatPath{1} = 'dropper_id';
info.MatPath{2} = 'timeout';
