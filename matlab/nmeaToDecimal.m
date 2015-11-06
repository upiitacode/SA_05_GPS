function [ decimalPosition ] = nmeaToDecimal( positionString, direction )
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
    if(strcmp(direction,'S') || strcmp(direction,'W'))
        sign = -1;
    else
        sign = 1;
    end
    tokens = regexp(positionString,'(\d+)(\d{2}.\d+)','tokens');
    hoursStr = tokens{1}{1};
    minutesStr = tokens{1}{2};
    hours = str2double(hoursStr);
    minutes = str2double(minutesStr);
    decimalPosition  = (hours + (minutes/60.0)) * sign;
end

