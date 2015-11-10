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
    end
    
end

