function [data, info] = controlModeRequest
%ControlMode gives an empty data for custom_interfaces/ControlModeRequest
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/ControlModeRequest';
[data.mode, info.mode] = ros.internal.ros2.messages.ros2.default_type('uint8',1,0);
info.MessageType = 'custom_interfaces/ControlModeRequest';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'mode';
