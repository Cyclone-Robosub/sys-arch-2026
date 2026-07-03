function [data, info] = executeTreeGoal
%ExecuteTreeGoal gives an empty data for btcpp_ros2_interfaces/ExecuteTreeGoal
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'btcpp_ros2_interfaces/ExecuteTreeGoal';
[data.target_tree, info.target_tree] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
[data.payload, info.payload] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
info.MessageType = 'btcpp_ros2_interfaces/ExecuteTreeGoal';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,2);
info.MatPath{1} = 'target_tree';
info.MatPath{2} = 'payload';
