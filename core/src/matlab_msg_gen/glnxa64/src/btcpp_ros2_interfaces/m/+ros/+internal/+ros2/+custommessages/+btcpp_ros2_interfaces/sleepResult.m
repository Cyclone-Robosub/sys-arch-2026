function [data, info] = sleepResult
%SleepResult gives an empty data for btcpp_ros2_interfaces/SleepResult
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'btcpp_ros2_interfaces/SleepResult';
[data.done, info.done] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
info.MessageType = 'btcpp_ros2_interfaces/SleepResult';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'done';
