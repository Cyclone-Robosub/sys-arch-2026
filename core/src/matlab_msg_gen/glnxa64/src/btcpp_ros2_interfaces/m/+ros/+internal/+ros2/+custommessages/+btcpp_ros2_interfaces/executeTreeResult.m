function [data, info] = executeTreeResult
%ExecuteTreeResult gives an empty data for btcpp_ros2_interfaces/ExecuteTreeResult
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'btcpp_ros2_interfaces/ExecuteTreeResult';
[data.node_status, info.node_status] = ros.internal.ros2.custommessages.btcpp_ros2_interfaces.nodeStatus;
info.node_status.MLdataType = 'struct';
[data.return_message, info.return_message] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
info.MessageType = 'btcpp_ros2_interfaces/ExecuteTreeResult';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,8);
info.MatPath{1} = 'node_status';
info.MatPath{2} = 'node_status.IDLE';
info.MatPath{3} = 'node_status.RUNNING';
info.MatPath{4} = 'node_status.SUCCESS';
info.MatPath{5} = 'node_status.FAILURE';
info.MatPath{6} = 'node_status.SKIPPED';
info.MatPath{7} = 'node_status.status';
info.MatPath{8} = 'return_message';
