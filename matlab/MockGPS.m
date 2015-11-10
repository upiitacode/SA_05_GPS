classdef MockGPS < handle
    properties
        counter = 0;
    end
    methods
         function obj = MockGPS()
         end
         function [gpsStruct] = readValidData(obj)
             counter = obj.counter;
             pos= [19.512434394991292, -99.12834450602531;
                19.512419225987752, -99.127593;
               19.512064018081364, -99.12781678140163]; 
            gpsStruct.latitude =  pos(counter+1,1);
            gpsStruct.longitude =  pos(counter+1,2);
            obj.counter = mod(counter+1,3);
         end
         function [gpsStruct] = readStableData(obj,n)
             gpsStruct = obj.readValidData();
         end
    end
end