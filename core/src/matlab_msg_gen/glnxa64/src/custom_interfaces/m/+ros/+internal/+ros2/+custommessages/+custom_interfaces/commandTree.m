function [data, info] = commandTree
%CommandTree gives an empty data for custom_interfaces/CommandTree
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/CommandTree';
[data.current_subtree, info.current_subtree] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
[data.current_command, info.current_command] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
[data.status, info.status] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
info.MessageType = 'custom_interfaces/CommandTree';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,3);
info.MatPath{1} = 'current_subtree';
info.MatPath{2} = 'current_command';
info.MatPath{3} = 'status';
