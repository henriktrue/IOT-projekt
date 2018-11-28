% Template MATLAB code for visualizing data from a channel as a 2D line
% plot using THINGSPEAKPLOT function.

% Prior to running this MATLAB code template, assign the channel ID to read
% data from to the 'readChannelID' variable. Also, assign the field ID
% within the channel that you want to read data from to plot. 

% TODO - Replace the [] with channel ID to read data from:
readChannelID = 578908;
% TODO - Replace the [] with the Field ID to read data from:
fieldID1 = 1;

% Channel Read API Key 
% If your channel is private, then enter the read API
% Key between the '' below: 
readAPIKey = '578908';

%% Read Data %%

points = 400;

[data, time] = thingSpeakRead(readChannelID, 'Field', fieldID1, 'NumPoints', points, 'ReadKey', readAPIKey);
    
time.TimeZone = '+00:00';
time.TimeZone = '+02:00';

lights_on = ones(1,points)*2316;
lights_off = ones(1,points)*19411;

R1 = 10000;
Vin = 5;

% calclulate resistance for every point in data vector
for c = 1:length(data)
    Vout(c) = ((3.3/4096)*data(c));
    R2(c) = (Vout(c)*R1)/(Vin-Vout(c));
end

%% Visualize Data %%
plot(time, R2, 'LineWidth',2) 
ylabel('NSL-19M51 resistance (Ω)')
ylim([0 33000])
hold on
plot(time, lights_off, '--', 'LineWidth',1.5)
hold on
plot(time, lights_on, '--', 'LineWidth',1.5) 
legend('Vout','lights off', 'lights on')