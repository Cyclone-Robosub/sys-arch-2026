function [data, info] = pwms
%Pwms gives an empty data for custom_interfaces/Pwms
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/Pwms';
[data.pwms, info.pwms] = ros.internal.ros2.messages.ros2.default_type('int32',8,0);
info.MessageType = 'custom_interfaces/Pwms';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'pwms';
