classdef MockSerialInput < handle
    %UNTITLED9 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        counter;
    end
    
    methods
        function obj = MockSerialInput()
            obj.counter = 0;
        end
        function close(obj)
        end
        function [line] = readLine(obj) 
            if( obj.counter > 10)
                line = '$GPRMC,210458.75,A,1930.74628,N,09907.70050,W,0.017,,101115,,,D*6D';
            elseif( obj.counter > 5)
                line = '$GPR,073718.00,A,1927.79512,N,09907.64413,W,1.351,,101115,,,A*6D';
            else
                line = '$GPRMC,073718.00,V,1927.79512,N,09907.64413,W,1.351,,101115,,,A*6D';
            end
                obj.counter = obj.counter + 1;
        end
    end
end

