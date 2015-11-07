% Test token parser

% Preconditions

%% Test 1: If empty cell is given an empty struct is returned
parsedS =parseGPRMC(struct());
assert(isempty(fieldnames(parsedS)));
%% Test 2: If formated cell is given struct is returned
stubStructure = struct( ...
'id','GPRMC',...
'time','075013.25',...
'status','A',...
'latitude','1927.79076',...
'n','N',...
'longitude','09907.64324',...
'e','W',...
'spd','0.477',...
'cog','',...
'date','061115',...
'mv','',...
'mve','',...
'mode','A',...
'cs','61'...
);
parseGPRMC(stubStructure)