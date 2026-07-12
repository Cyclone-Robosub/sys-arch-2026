function [data, info] = debug
%Debug gives an empty data for custom_interfaces/Debug
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/Debug';
[data.message, info.message] = ros.internal.ros2.messages.ros2.char('char',256,NaN,0);
info.MessageType = 'custom_interfaces/Debug';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'message';
