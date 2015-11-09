% Test Trajectory

% Preconditions

%% Test 1: It calculate Affine transformation matrix 
p1 = [50 50]';
q1 = [200 200]';
p2 = [50 100]';
q2 = [200 300]';
p3 = [100 50]';
q3 = [300 200]';

P = [p1 p2 p3];
Q = [q1 q2 q3];

[A B] = MapTranslator.getMatrix(P,Q);

qprime = A*p1+B;
assert(isequal(qprime,q1));
qprime = A*p2+B;
assert(isequal(qprime,q2));
qprime = A*p3+B;
assert(isequal(qprime,q3));
%%
