% Template MATLAB code for visualizing data from a channel as a 2D line
% plot using THINGSPEAKPLOT function.

% Prior to running this MATLAB code template, assign the channel ID to read
% data from to the 'readChannelID' variable. Also, assign the field ID
% within the channel that you want to read data from to plot. 

% TODO - Replace the [] with channel ID to read data from:
readChannelID = 573876;
% TODO - Replace the [] with the Field ID to read data from:
fieldID1 = 1;

% Channel Read API Key 
% If your channel is private, then enter the read API
% Key between the '' below: 
readAPIKey = '573876';

%% Read Data %%

points = 100;

[data, time] = thingSpeakRead(readChannelID, 'Field', fieldID1, 'NumPoints', points, 'ReadKey', readAPIKey);

time.TimeZone = '+00:00';
time.TimeZone = '+02:00';

temp = ((3.3/4096)*data)*100;

%% Visualize Data %%

plot(time, temp, 'LineWidth',2) 
ylabel('degrees (C)')
ylim([10 35])