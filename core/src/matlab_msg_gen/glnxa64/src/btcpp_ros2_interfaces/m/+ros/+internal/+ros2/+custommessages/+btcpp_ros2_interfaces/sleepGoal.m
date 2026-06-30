function [data, info] = sleepGoal
%SleepGoal gives an empty data for btcpp_ros2_interfaces/SleepGoal
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'btcpp_ros2_interfaces/SleepGoal';
[data.msec_timeout, info.msec_timeout] = ros.internal.ros2.messages.ros2.default_type('int32',1,0);
info.MessageType = 'btcpp_ros2_interfaces/SleepGoal';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'msec_timeout';
