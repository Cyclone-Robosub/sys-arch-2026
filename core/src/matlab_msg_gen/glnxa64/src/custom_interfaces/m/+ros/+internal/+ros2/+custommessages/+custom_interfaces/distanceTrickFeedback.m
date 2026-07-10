function [data, info] = distanceTrickFeedback
%DistanceTrickFeedback gives an empty data for custom_interfaces/DistanceTrickFeedback
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/DistanceTrickFeedback';
info.MessageType = 'custom_interfaces/DistanceTrickFeedback';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,0);
