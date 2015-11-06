% Test input parser

% Preconditions

%% Test 1: First case of datasheet
result =nmeaToDecimal('4717.112671','S');
error = abs(-47.28521118 - result);
assert(error < 0.01 );
%% Test 2: North
result =nmeaToDecimal('4717.112671','N');
error = abs(47.28521118 - result);
assert(error < 0.01 );
%% Test 3: Weast
result =nmeaToDecimal('00833.914843','W');
error = abs(-8.56524738 - result);
assert(error < 0.01 );
%% Test 4: Weast
result =nmeaToDecimal('00833.914843','E');
error = abs(8.56524738 - result);
assert(error < 0.01 );
