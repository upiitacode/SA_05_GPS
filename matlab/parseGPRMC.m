function [ gprmcStruct ] = parseGPRMC(gpsStruct)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

gprmcStruct = struct();
if(~isempty(fieldnames(gpsStruct)))
    if(strcmp(gpsStruct.id, 'GPRMC'))
        % do stuff
        if(strcmp(gpsStruct.status,'A'))
            gprmcStruct.('isValid') = true;
            gprmcStruct.('latitude') = nmeaToDecimal(gpsStruct.latitude,gpsStruct.n);
            gprmcStruct.('longitude') = nmeaToDecimal(gpsStruct.longitude,gpsStruct.e);
            gprmcStruct.('velocity') = str2double(gpsStruct.spd) *1.852; % knots to km/h
            gprmcStruct.('course') = str2double(gpsStruct.cog); %already in degrees 
        else
            gprmcStruct.('isValid') = false;
            gprmcStruct.('latitude') = 0;
            gprmcStruct.('longitude') = 0;
            gprmcStruct.('velocity') = 0;
            gprmcStruct.('course') = 0;
        end
         gprmcStruct.('time') = gpsStruct.time;
         gprmcStruct.('date') = gpsStruct.date;
    end
end
end

