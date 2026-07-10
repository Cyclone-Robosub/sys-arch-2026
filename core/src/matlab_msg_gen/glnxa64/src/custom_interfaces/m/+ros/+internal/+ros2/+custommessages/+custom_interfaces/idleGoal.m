function [data, info] = idleGoal
%IdleGoal gives an empty data for custom_interfaces/IdleGoal
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/IdleGoal';
info.MessageType = 'custom_interfaces/IdleGoal';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,0);
