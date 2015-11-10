classdef InteractiveGPSMock < handle
    %UNTITLED12 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        time =  0;
        lastLat = 0;
        lastLon = 0;
    end
    
    methods
        function [gpsStruct] = readValidData(obj)
            gpsStruct.latitude =  input('Enter latitude:\n');
            gpsStruct.longitude =  input('Enter longitude:\n');  
            gpsStruct.time = obj.time;
            if(obj.time == 0)
                gpsStruct.velocity = 0;
                obj.lastLat = gpsStruct.latitude;
                obj.lastLon = gpsStruct.longitude;
            else
                delta = [obj.lastLat,obj.lastLon] - [gpsStruct.latitude, gpsStruct.longitude];
                gpsStruct.velocity = norm(delta);
            end
            obj.time = obj.time + 1;
            obj.lastLat = gpsStruct.latitude;
            obj.lastLon = gpsStruct.longitude;
         end
         function [gpsStruct] = readStableData(obj,n)
             gpsStruct = obj.readValidData();
         end
    end
    
end
