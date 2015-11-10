classdef GPS
    %UNTITLED3 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        serialInput
    end
    
    methods
         function obj =GPS(serialInput)
            obj.serialInput = serialInput;
         end
         function [gpsStruct] = readValidData(obj)
            isValid = false;
            while ~isValid
                gpsString = obj.serialInput.readLine();
                tokenizedData = tokenizeLine(gpsString);
                stringStruct = parseToken(tokenizedData);
                parsedStruct = parseGPRMC(stringStruct)
                if(~(isempty(fieldnames(parsedStruct))))
                    isValid = parsedStruct.isValid;
                end
            end
            gpsStruct = parsedStruct;
         end
         function [gpsStruct] = readStableData(obj,n)
            stable_lat = 0;
            stable_lon = 0;
            for i = 1 : 10
                gpsData = obj.readValidData();
                stable_lat = stable_lat + gpsData.latitude;
                stable_lon = stable_lon + gpsData.longitude;
            end
            stable_lat = stable_lat/n;
            stable_lon = stable_lon/n;
            gpsStruct.latitude = stable_lat;
            gpsStruct.longitude = stable_lon;
        end

    end
    
end

