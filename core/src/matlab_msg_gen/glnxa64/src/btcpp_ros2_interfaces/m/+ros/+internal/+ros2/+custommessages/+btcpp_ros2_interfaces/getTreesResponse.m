function [data, info] = getTreesResponse
%GetTrees gives an empty data for btcpp_ros2_interfaces/GetTreesResponse
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'btcpp_ros2_interfaces/GetTreesResponse';
[data.tree_ids, info.tree_ids] = ros.internal.ros2.messages.ros2.char('string',NaN,NaN,0);
info.MessageType = 'btcpp_ros2_interfaces/GetTreesResponse';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,1);
info.MatPath{1} = 'tree_ids';
