function [ p ] = readAndTransform( )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
    load('transformMatrix');
    gpsData = resetRead();
    q = [gpsData.longitude; gpsData.latitude];
    p =Aqp *q + Bqp;
end

