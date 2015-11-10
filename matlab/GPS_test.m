% Test token parser

% Preconditions

%% Test 1: Only return valid data
parsedS =parseToken({});
assert(isempty(fieldnames(parsedS)));mock =  MockSerialInput();
gps = GPS(mock);
gpsStruct = gps.readValidData()
%% Test 2: 
parsedS =parseToken({});
assert(isempty(fieldnames(parsedS)));mock =  MockSerialInput();
gps = GPS(mock);
gpsStruct = gps.readStableData(10)
%%
q = [gpsData.longitude; gpsData.latitude];
Q(:,3) = q