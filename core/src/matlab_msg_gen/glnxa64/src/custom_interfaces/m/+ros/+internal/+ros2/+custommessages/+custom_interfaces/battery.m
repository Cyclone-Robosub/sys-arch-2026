function [data, info] = battery
%Battery gives an empty data for custom_interfaces/Battery
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/Battery';
[data.voltage, info.voltage] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
[data.current, info.current] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
info.MessageType = 'custom_interfaces/Battery';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,2);
info.MatPath{1} = 'voltage';
info.MatPath{2} = 'current';
