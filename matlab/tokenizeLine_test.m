% Test input parser

% Preconditions

%% Test 1: If empty string is given returns empty cell
result =tokenizeLine('');
assert(isempty(result));
assert(iscell(result));
%% Test 2: that well formated string is parsed to a cell
parsed_cell =tokenizeLine('$GPRMC,075013.25,A,1927.79076,N,09907.64324,W,0.477,,061115,,,A*61');
expected_cell = {'GPRMC','075013.25','A','1927.79076','N','09907.64324','W','0.477','','061115','','','A','61'};
assert(isequal(parsed_cell{1},expected_cell));
%% Test 3: that well formated string is parsed to a cell
parsed_cell =tokenizeLine('$GPRMC,082906.00,V,,,,,,,061115,,,N*7A');
expected_cell = {'GPRMC','082906.00','V','','','','','','','061115','','','N','7A'};
assert(isequal(parsed_cell{1},expected_cell));
