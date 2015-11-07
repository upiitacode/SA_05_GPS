% Test Trajectory

% Preconditions

%% Test 1: Position is set on creation
trajectory  = Trajectory({[4 5]},[1 1],0.2);
position = trajectory.getPosition();
assert(isequal(position,[1 1]));

error = trajectory.getNormalError();
assert(isequal(error, 0));

completion = trajectory.getSegmentCompletion();
assert(isequal(completion, 0));

outOfCourse = trajectory.isOutOfCourse();
assert(isequal(outOfCourse, false));
assert(~trajectory.isComplete);
%% Test 1: Position is set on creation
trajectory  = Trajectory({[4 5]},[1 1],0.2);
position = trajectory.getPosition();
assert(isequal(position,[1 1]));

error = trajectory.getNormalError();
assert(isequal(error, 0));

completion = trajectory.getSegmentCompletion();
assert(isequal(completion, 0));

completion = trajectory.getTotalCompletion();
assert(isequal(completion, 0));

sLength = trajectory.getSegmentLength();
assert(isequal(sLength, 5));

tLength  = trajectory.getTotalLength();
assert(isequal(tLength,5));

nCheckpoint = trajectory.getNextCheckpointIndex();
assert(isequal(nCheckpoint, 2));
%% Test 2: Lengths can be calculated with several points
trajectory  = Trajectory({[4 5],[8 8],[14,16]},[1 1],0.2);
position = trajectory.getPosition();
tLength  = trajectory.getTotalLength();
assert(isequal(tLength,20));
sLength = trajectory.getSegmentLength();
assert(isequal(sLength, 5));
%% Test 3: Can update checkpoint
trajectory  = Trajectory({[4 5],[8 8],[14,16]},[1 1],0.2);
nCheckpoint = trajectory.getNextCheckpointIndex();
assert(isequal(nCheckpoint, 2));

trajectory.setPosition([4 5]);
nCheckpoint = trajectory.getNextCheckpointIndex();
assert(isequal(nCheckpoint, 3));

sLength = trajectory.getSegmentLength();
assert(isequal(sLength, 5));

trajectory.setPosition([8.1 7.9]);
nCheckpoint = trajectory.getNextCheckpointIndex();
assert(isequal(nCheckpoint, 4));

sLength = trajectory.getSegmentLength();
assert(isequal(sLength, 10));
%% Tests 4: Segment Completion can be calculated
trajectory  = Trajectory({[3 3],[8 8]},[1 1],0.2);
trajectory.setPosition([2 2]);
completion = trajectory.getSegmentCompletion();
assert(isequal(completion, 0.5));
error = trajectory.getNormalError();
assert(isequal(error, 0));
%% Tests 5: Trajectory error can be calculated
trajectory  = Trajectory({[3 3],[8 8]},[1 1],0.2);
trajectory.setPosition([1 2]);
error = trajectory.getNormalError();
assert(abs(error - sqrt(1/2)) < 0.0001);
%% Tests 6: can tell if out of course
trajectory  = Trajectory({[3 3],[8 8]},[1 1],0.2);
outOfCourse = trajectory.isOutOfCourse();
assert(isequal(outOfCourse, false));

trajectory.setPosition([2 2]);
outOfCourse = trajectory.isOutOfCourse();
assert(isequal(outOfCourse, false));

trajectory.setPosition([1.5 1.5]);
outOfCourse = trajectory.isOutOfCourse();
assert(isequal(outOfCourse, true));

trajectory.setPosition([2.5 2.5]);
outOfCourse = trajectory.isOutOfCourse();
assert(isequal(outOfCourse, false));
%% Tests 7 : total completion can be calculated
trajectory  = Trajectory({[3 3],[1 5]},[1 1],0.2);
trajectory.setPosition([2 2]);
completion = trajectory.getTotalCompletion();
assert(isequal(completion, 0.25));

trajectory.setPosition([3 3]);
completion = trajectory.getTotalCompletion();
assert(isequal(completion, 0.50));

trajectory.setPosition([2 4]);
completion = trajectory.getTotalCompletion();
assert(isequal(completion, 0.75));

trajectory.setPosition([1 5]);
completion = trajectory.getTotalCompletion();
assert(isequal(completion, 1));

assert(trajectory.isComplete);