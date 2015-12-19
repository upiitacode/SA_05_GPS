function [ gpsData ] = resetRead()
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    serial = SerialInput('COM6')
    gps = GPS(serial);
    gpsData = gps.readValidData();
    serial.close()
end

