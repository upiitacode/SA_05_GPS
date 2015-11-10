clear all
serial  = SerialInput('COM6')
%%
gps = GPS(serial);
%%

gpsData = gps.readStableData(10);
q = [gpsData.longitude; gpsData.latitude];
%%
Q(:,3) = q
%%
serial.close()