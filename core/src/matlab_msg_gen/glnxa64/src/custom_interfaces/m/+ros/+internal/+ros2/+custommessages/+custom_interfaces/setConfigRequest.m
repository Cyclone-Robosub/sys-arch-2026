function [data, info] = setConfigRequest
%SetConfig gives an empty data for custom_interfaces/SetConfigRequest
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/SetConfigRequest';
[data.config_data, info.config_data] = ros.internal.ros2.custommessages.custom_interfaces.config;
info.config_data.MLdataType = 'struct';
info.MessageType = 'custom_interfaces/SetConfigRequest';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,7);
info.MatPath{1} = 'config_data';
info.MatPath{2} = 'config_data.speed_of_sound';
info.MatPath{3} = 'config_data.mounting_rotation_offset';
info.MatPath{4} = 'config_data.acoustic_enabled';
info.MatPath{5} = 'config_data.dark_mode_enabled';
info.MatPath{6} = 'config_data.range_mode';
info.MatPath{7} = 'config_data.periodic_cycling_enabled';
