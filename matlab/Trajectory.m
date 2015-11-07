classdef Trajectory < handle
    %UNTITLED11 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        pointList;
        positionTolerance;
        next_checkpoint = 2;
        last_checkpoint = 1;
        last_position = 0;
        current_position = 0;
        isComplete = false;
    end
    
    methods

        function obj = Trajectory(points, position, tolerance)
            obj.pointList = [position points];
            obj.current_position = position;
            obj.last_position = position;
            obj.positionTolerance = tolerance;
        end

        function [outOfCourse] = isOutOfCourse(obj)
            currentCompletion = obj.getSegmentCompletion();
            lastCompletion = obj.getUnitaryCompletion(obj.last_position);
            outOfCourse =  lastCompletion > currentCompletion;
        end
        
        function [len] = getLengthUpToCheckpoint(obj, checkpoint)
            len  = 0;
            for i = [1 : (checkpoint -1)]  
                len  = len + norm(obj.pointList{i} - obj.pointList{i+1});
            end
        end
        function [len] = getTotalLength(obj)
             len = obj.getLengthUpToCheckpoint(length(obj.pointList));
        end

        function [len] = getSegmentLength(obj)
            len  = norm(obj.pointList{obj.last_checkpoint} - obj.pointList{obj.next_checkpoint});
        end

        function [unitaryCompletion] = getSegmentCompletion(obj)
           unitaryCompletion = obj.getUnitaryCompletion(obj.current_position);
    	end

        function [unitaryCompletion] = getTotalCompletion(obj)
             unitarySegmentCompletion = obj.getUnitaryCompletion(obj.current_position);
             segmentLength = obj.getSegmentLength();
             segmentCompletion = unitarySegmentCompletion*segmentLength();
             completion  = segmentCompletion + obj.getLengthUpToCheckpoint(obj.last_checkpoint);
             unitaryCompletion = completion/obj.getTotalLength();
        end

        function [error] = getNormalError(obj)
             Ra = obj.pointList{obj.last_checkpoint}';
            Rb = obj.pointList{obj.next_checkpoint}';
            Rc = obj.current_position';
            [~, error] = getProgressAndError(Ra,Rb,Rc);
        end

        function setPosition(obj,position)
            obj.last_position = obj.current_position;
            obj.current_position = position;
            nextCP_position = obj.pointList{obj.next_checkpoint};
            if (norm(nextCP_position - position) < obj.positionTolerance)
                if (obj.next_checkpoint < length(obj.pointList))
                    obj.next_checkpoint = obj.next_checkpoint + 1;
                    obj.last_checkpoint = obj.last_checkpoint + 1;
                else
                    obj.isComplete = true;
                end
            end
        end

        function [position] = getPosition(obj)
            position = obj.current_position;
        end
        
        function [index]  = getNextCheckpointIndex(obj)
            index = obj.next_checkpoint;
        end
        
        function [unitaryCompletion] = getUnitaryCompletion(obj, position)
            Ra = obj.pointList{obj.last_checkpoint}';
            Rb = obj.pointList{obj.next_checkpoint}';
            Rc = position';
            completion  = getProgressAndError(Ra,Rb,Rc);
            unitaryCompletion = completion/obj.getSegmentLength(); 
        end

        end
    
end

function [progress, error] = getProgressAndError(Ra,Rb,Rc)
U = (Rb - Ra);
rotationMatrix = [0 -1; 1 0];
u = U/norm(U);
uR = rotationMatrix*u;
B = [u uR];
k = inv(B)*(Rc - Ra);
progress = k(1);
error = k(2);
end