function [data, info] = sleepFeedback
%SleepFeedback gives an empty data for btcpp_ros2_interfaces/SleepFeedback
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'btcpp_ros2_interfaces/SleepFeedback';
[data.cycle, info.cycle] = ros.internal.ros2.messages.ros2.default_type('int32',1,0);
info.MessageType = 'btcpp_ros2_interfaces/SleepFeedback';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'cycle';
