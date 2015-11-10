classdef SerialInput < handle
    %UNTITLED9 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        serial_file
    end
    
    methods
        function obj =SerialInput(comString)
            obj.serial_file = serial(comString);
            fopen(obj.serial_file);
            obj.readLine();
        end
        function close(obj)
            fclose(obj.serial_file);
        end
        function [readStr] = readLine(obj) 
            readStr =fgetl(obj.serial_file)
        end
    end
end

