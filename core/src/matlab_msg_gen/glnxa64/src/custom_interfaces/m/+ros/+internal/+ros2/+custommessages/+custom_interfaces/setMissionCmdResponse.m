function [data, info] = setMissionCmdResponse
%SetMissionCmd gives an empty data for custom_interfaces/SetMissionCmdResponse
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/SetMissionCmdResponse';
[data.success, info.success] = ros.internal.ros2.messages.ros2.default_type('logical',1,0);
info.MessageType = 'custom_interfaces/SetMissionCmdResponse';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'success';
