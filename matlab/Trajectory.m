classdef Trajectory < handle
    %UNTITLED11 Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        pointList;
        positionTolerance;
        next_checkpoint = 2;
        last_checkpoint = 1;
        last_position = 0.5;
        current_position = 0.5;
    end
    
    methods

        function obj = Trajectory(points, position, tolerance)
            obj.pointList = [position points];
            obj.current_position = position;
            obj.last_position = position;
            obj.positionTolerance = tolerance;
        end

        function [outOfCourse] = isOutOfCourse(obj)
            outOfCourse  = false;
        end

        function [len] = getTotalLength(obj)
            len  = 0;
            for i = [1 : (length(obj.pointList) - 1)]
                len  = len + norm(obj.pointList{i} - obj.pointList{i+1});
            end
        end

        function [len] = getSegmentLength(obj)
            len  = norm(obj.pointList{obj.last_checkpoint} - obj.pointList{obj.next_checkpoint});
        end

        function [completion] = getSegmentCompletion(obj)
            completion  = 0;
    	end

        function [completion] = getTotalCompletion(obj)
            completion  = 0;
        end

        function [error] = getNormalError(obj)
            error  = 0;
        end

        function setPosition(obj,position)
            obj.current_position = position;
	    nextCP_position = obj.pointList{obj.next_checkpoint};
	    if (norm(nextCP_position - position) < obj.positionTolerance)
	    	obj.next_checkpoint = obj.next_checkpoint + 1;
	    	obj.last_checkpoint = obj.last_checkpoint + 1;
	    end
        end

        function [position] = getPosition(obj)
            position = obj.current_position;
        end
        
        function [index]  = getNextCheckpointIndex(obj)
            index = obj.next_checkpoint;
        end

        end

end
