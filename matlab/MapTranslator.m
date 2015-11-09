classdef MapTranslator
    %UNTITLED4 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
    end
    methods
    end
    methods(Static)
        function [A, B] = getMatrix(P,Q)
            deltaP = [P(:,1)-P(:,2), P(:,2)-P(:,3)];
            deltaQ = [Q(:,1)-Q(:,2), Q(:,2)-Q(:,3)];
            A = deltaQ*inv(deltaP);
            B= sum((Q-A*P)')'/size(Q,2);
        end
    end
    
end

