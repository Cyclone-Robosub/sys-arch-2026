function [data, info] = setMissionCmdRequest
%SetMissionCmd gives an empty data for custom_interfaces/SetMissionCmdRequest
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/SetMissionCmdRequest';
[data.command_id, info.command_id] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
[data.parameter_name, info.parameter_name] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
[data.value, info.value] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
info.MessageType = 'custom_interfaces/SetMissionCmdRequest';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,3);
info.MatPath{1} = 'command_id';
info.MatPath{2} = 'parameter_name';
info.MatPath{3} = 'value';
