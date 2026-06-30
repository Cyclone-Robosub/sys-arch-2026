function [data, info] = seekObjectFeedback
%SeekObjectFeedback gives an empty data for custom_interfaces/SeekObjectFeedback
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/SeekObjectFeedback';
info.MessageType = 'custom_interfaces/SeekObjectFeedback';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,0);
