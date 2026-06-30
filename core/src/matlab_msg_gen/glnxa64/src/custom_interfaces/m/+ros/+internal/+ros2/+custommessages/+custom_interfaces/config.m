function [data, info] = config
%Config gives an empty data for custom_interfaces/Config
% Copyright 2019-2021 The MathWorks, Inc.
data = struct();
data.MessageType = 'custom_interfaces/Config';
[data.speed_of_sound, info.speed_of_sound] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
[data.mounting_rotation_offset, info.mounting_rotation_offset] = ros.internal.ros2.messages.ros2.default_type('single',1,0);
[data.acoustic_enabled, info.acoustic_enabled] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
[data.dark_mode_enabled, info.dark_mode_enabled] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
[data.range_mode, info.range_mode] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
[data.periodic_cycling_enabled, info.periodic_cycling_enabled] = ros.internal.ros2.messages.ros2.char('string',1,NaN,0);
info.MessageType = 'custom_interfaces/Config';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,6);
info.MatPath{1} = 'speed_of_sound';
info.MatPath{2} = 'mounting_rotation_offset';
info.MatPath{3} = 'acoustic_enabled';
info.MatPath{4} = 'dark_mode_enabled';
info.MatPath{5} = 'range_mode';
info.MatPath{6} = 'periodic_cycling_enabled';
