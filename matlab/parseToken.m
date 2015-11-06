function [ parsedStruct ] = parseToken( tokens )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here 
parsedStruct = struct();
if ~isempty(tokens)
	parsedStruct.('id') = tokens{1}{1};
	parsedStruct.('time') = tokens{1}{2};
	parsedStruct.('status') = tokens{1}{3};
	parsedStruct.('latitude') = tokens{1}{4};
	parsedStruct.('n') = tokens{1}{5};
	parsedStruct.('longitude') = tokens{1}{6};
	parsedStruct.('e') = tokens{1}{7};
	parsedStruct.('spd') = tokens{1}{8};
	parsedStruct.('cog') = tokens{1}{9};
	parsedStruct.('date') = tokens{1}{10};
	parsedStruct.('mv') = tokens{1}{11};
	parsedStruct.('mve') = tokens{1}{12};
	parsedStruct.('mode') = tokens{1}{13};
	parsedStruct.('cs') = tokens{1}{14};
end

end

