clear all
load('transformMatrix');
yellow = uint8([255 255 0]); % [R G B]; class of yellow must match class of I
blue = uint8([0 0 255]); % [R G B]; class of yellow must match class of IG
green= uint8([0 255 0]); % [R G B]; class of yellow must match class of I
red= uint8([255 0 0]); % [R G B]; class of yellow must match class of I
cyan= uint8([0 255 255]); % [R G B]; class of yellow must match class of I

yellowCirclePainter = vision.ShapeInserter('Shape','Circles','BorderColor','Custom','CustomBorderColor',yellow,'LineWidth',5);
blueCirclePainter = vision.ShapeInserter('Shape','Circles','BorderColor','Custom','CustomBorderColor',blue,'LineWidth',5);
greenCirclePainter = vision.ShapeInserter('Shape','Circles','BorderColor','Custom','CustomBorderColor',green,'LineWidth',5);
redCirclePainter = vision.ShapeInserter('Shape','Circles','BorderColor','Custom','CustomBorderColor',yellow,'LineWidth',5);
blueCirclePainter = vision.ShapeInserter('Shape','Circles','BorderColor','Custom','CustomBorderColor',blue,'LineWidth',5);
greenCirclePainter = vision.ShapeInserter('Shape','Circles','BorderColor','Custom','CustomBorderColor',green,'LineWidth',5);


I = imread('upiita_02.png');
axes(gca);
imshow(I); 
%%
[x , y] = getpts(gca);
P = [x,y]';
for i = 1:size(P,2); 
    Pcell{i} = P(:,i)';
end
p = readAndTransform();
trajectory  = Trajectory(Pcell,p',20);
%%
while ~trajectory.isComplete
    axes(gca);
    p = readAndTransform(); 
    pt = p'
    trajectory.setPosition(pt);
    nCheckpoint = trajectory.getNextCheckpointIndex();
    destiny = trajectory.pointList{nCheckpoint};
    points = [pt, ones(size(pt,1),1)*10]
    points = int32(points)
    J = step(greenCirclePainter, I, int32([destiny 20]));
    K = step(blueCirclePainter, J, points);
    imshow(K); 
    pause(0.25)
    
end
%%
J = step(yellowCirclePainter, I, int32([destiny 20]));
K = step(blueCirclePainter, J, points);
imshow(K); 
disp('Recorrido Terminado');