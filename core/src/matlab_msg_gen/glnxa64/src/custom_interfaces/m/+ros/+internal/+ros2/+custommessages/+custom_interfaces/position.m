function [data, info] = position
%Position gives an empty data for custom_interfaces/Position
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/Position';
[data.position, info.position] = ros.internal.ros2.messages.geometry_msgs.pose;
info.position.MLdataType = 'struct';
info.MessageType = 'custom_interfaces/Position';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,10);
info.MatPath{1} = 'position';
info.MatPath{2} = 'position.position';
info.MatPath{3} = 'position.position.x';
info.MatPath{4} = 'position.position.y';
info.MatPath{5} = 'position.position.z';
info.MatPath{6} = 'position.orientation';
info.MatPath{7} = 'position.orientation.x';
info.MatPath{8} = 'position.orientation.y';
info.MatPath{9} = 'position.orientation.z';
info.MatPath{10} = 'position.orientation.w';
