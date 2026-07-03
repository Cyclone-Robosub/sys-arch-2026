function [data, info] = executeTreeFeedback
%ExecuteTreeFeedback gives an empty data for btcpp_ros2_interfaces/ExecuteTreeFeedback
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'btcpp_ros2_interfaces/ExecuteTreeFeedback';
[data.message, info.message] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
info.MessageType = 'btcpp_ros2_interfaces/ExecuteTreeFeedback';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'message';
