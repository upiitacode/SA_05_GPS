function [ tokens ] = tokenizeLine( line )
%UNTITLED Summary of this function goes here
%   Detailed explanat
tokens = regexp(line,'\$(.*?),(.*?),(.*?),(.*?),(.*?),(.*?),(.*?),(.*?),(.*?),(.*?),(.*?),(.*?),(\w+)\*(\w+)','tokens');
end
