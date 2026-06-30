function [data, info] = dropperFeedback
%DropperFeedback gives an empty data for custom_interfaces/DropperFeedback
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/DropperFeedback';
info.MessageType = 'custom_interfaces/DropperFeedback';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,0);
