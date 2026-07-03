function [data, info] = nodeStatus
%NodeStatus gives an empty data for btcpp_ros2_interfaces/NodeStatus
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'btcpp_ros2_interfaces/NodeStatus';
[data.IDLE, info.IDLE] = ros.internal.ros2.messages.ros2.default_type('uint8',1,0, 0, [NaN]);
[data.RUNNING, info.RUNNING] = ros.internal.ros2.messages.ros2.default_type('uint8',1,0, 1, [NaN]);
[data.SUCCESS, info.SUCCESS] = ros.internal.ros2.messages.ros2.default_type('uint8',1,0, 2, [NaN]);
[data.FAILURE, info.FAILURE] = ros.internal.ros2.messages.ros2.default_type('uint8',1,0, 3, [NaN]);
[data.SKIPPED, info.SKIPPED] = ros.internal.ros2.messages.ros2.default_type('uint8',1,0, 4, [NaN]);
[data.status, info.status] = ros.internal.ros2.messages.ros2.default_type('uint8',1,0);
info.MessageType = 'btcpp_ros2_interfaces/NodeStatus';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,6);
info.MatPath{1} = 'IDLE';
info.MatPath{2} = 'RUNNING';
info.MatPath{3} = 'SUCCESS';
info.MatPath{4} = 'FAILURE';
info.MatPath{5} = 'SKIPPED';
info.MatPath{6} = 'status';
