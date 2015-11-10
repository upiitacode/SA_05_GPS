clear all
gps = InteractiveGPSMock();
load('transformMatrix','Apq','Bpq','Aqp','Bqp');
disp('Select 3 points in map')
yellow = uint8([255 255 0]); % [R G B]; class of yellow must match class of I
blue = uint8([0 0 255]); % [R G B]; class of yellow must match class of IG
green= uint8([0 255 0]); % [R G B]; class of yellow must match class of I

yellowCirclePainter = vision.ShapeInserter('Shape','Circles','BorderColor','Custom','CustomBorderColor',yellow,'LineWidth',5);
blueCirclePainter = vision.ShapeInserter('Shape','Circles','BorderColor','Custom','CustomBorderColor',blue,'LineWidth',5);
greenCirclePainter = vision.ShapeInserter('Shape','Circles','BorderColor','Custom','CustomBorderColor',green,'LineWidth',5);

I = imread('upiita_02.png');
axes(gca);
imshow(I); 
%%
gpsData = gps.readValidData();
q = [gpsData.longitude; gpsData.latitude];
p =Aqp * q + Bqp; 
pt = p'
points = [pt, ones(size(pt,1),1)*10]
points = int32(points)
K = step(blueCirclePainter, I, points);
imshow(K); 
%%