clear all
gps = MockGPS();

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
[x , y] = getpts(gca);
P = [x,y]';
for i = 1:3
    readString = input('Go to circle, Press any key to continue\n');
    stablePos = gps.readStableData(10);
    Q(:,i) = [stablePos.longitude; stablePos.latitude];
end
%%
[Apq Bpq] = MapTranslator.getMatrix(P,Q)
[Aqp Bqp] = MapTranslator.getMatrix(Q,P)
%%
save('transformMatrix','Apq','Bpq','Aqp','Bqp');
%% Coordinate to pixel

