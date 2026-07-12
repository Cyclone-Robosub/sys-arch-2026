function [data, info] = getMissionCmdRequest
%GetMissionCmd gives an empty data for custom_interfaces/GetMissionCmdRequest
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/GetMissionCmdRequest';
[data.command_id, info.command_id] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
info.MessageType = 'custom_interfaces/GetMissionCmdRequest';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'command_id';
