function [data, info] = objectRelativeWaypointFeedback
%ObjectRelativeWaypointFeedback gives an empty data for custom_interfaces/ObjectRelativeWaypointFeedback
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/ObjectRelativeWaypointFeedback';
info.MessageType = 'custom_interfaces/ObjectRelativeWaypointFeedback';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,0);
