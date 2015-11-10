% Test token parser

% Preconditions

%% Test 1: Only return valid data
parsedS =parseToken({});
assert(isempty(fieldnames(parsedS)));mock =  MockSerialInput();
gps = GPS(mock);
gpsStruct = gps.readValidData()