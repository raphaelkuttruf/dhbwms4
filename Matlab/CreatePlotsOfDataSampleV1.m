% DHBW Mosbach
% Mechatronische Systeme 4
% Dr.-Ing. Vanessa Romero Segovia
% MT17B Gruppe 3 (Sarah Plieninger, Fabian Redaoui, Raphael Kuttruf)

% https://de.mathworks.com/help/matlab/math/array-indexing.html
% https://de.mathworks.com/help/matlab/ref/strcat.html
% https://de.mathworks.com/help/matlab/creating_plots/combine-multiple-plots.html
% https://de.mathworks.com/help/matlab/creating_plots/add-legend-to-graph.html
% https://de.mathworks.com/help/matlab/data_analysis/time-series-objects.html
% https://de.mathworks.com/matlabcentral/answers/64158-multiple-plots-on-a-subplot

clear
clc
sourcefilename = 'DataSample';
controllertype = 'PID';
tuningmethod = 'AMIGO';
destinationfileidentifier = strcat(controllertype,'_',tuningmethod,'X'); % make this unique name, else you will overwrite !
samplefrequency = 50;
tuningmethod = strcat(tuningmethod, ')');
Data = load(strcat(sourcefilename, '.mat'));
timeseries = Data.DataSample(:, 1);
timeseriesdatadimension=  size(timeseries.Data);
%timeseriesdata = getdatasamples(timeseries, (1:260)); % Selected Samplerange
timeseriesdata = getdatasamples(timeseries, (1:timeseriesdatadimension(1,1))); % All samples!
SampleNr = timeseriesdata(:, 1);
time = SampleNr / samplefrequency;
SystemState_mV = timeseriesdata(:, 2);
SystemState_mm = timeseriesdata(:, 3);
SystemStatePostFilter_mV = timeseriesdata(:, 4);
SystemStatePostFilter_mm = timeseriesdata(:, 5);
ControllerSetpoint_mm = timeseriesdata(:, 6);
ConrollerOutput_mV = timeseriesdata(:, 7);
ActuatorOutput_mV = timeseriesdata(:, 8);
ActuatorOutput_Bit = timeseriesdata(:, 9);
Controller_P = timeseriesdata(:, 10);
Controller_I = timeseriesdata(:, 11);
Controller_D = timeseriesdata(:, 12);

figure(1)
subplot(2, 1, 1)
plot(time, ControllerSetpoint_mm, 'DisplayName', 'Setpoint')
hold on% more plots in the same diagram
plot(time, SystemState_mm, 'DisplayName', 'Actual Level')
hold off
title(strcat(controllertype, ' Controller Water Level Process (', tuningmethod))
xlabel('Time [s]')
ylabel('Water Level [mm]')
legend
subplot(2, 1, 2)
plot(time, ConrollerOutput_mV, 'DisplayName', 'Controller Outputsignal')
hold on% more plots in the same diagram
plot(time, ActuatorOutput_mV, 'DisplayName', 'Actuator Output')
hold off
title(strcat(controllertype, ' Controller Water Level Process (', tuningmethod))
xlabel('Time [s]')
ylabel('Outputsignal [mV]')
legend
set(gcf, 'Position', get(0, 'Screensize'));
savefig(strcat('Plot_Controller_', destinationfileidentifier, '.fig'))
saveas(gcf, strcat('Plot_Controller_', destinationfileidentifier, '.png'))

figure(2)
subplot(2, 1, 1)
plot(time, SystemState_mV, 'DisplayName', 'Raw')
hold on% more plots in the same diagram
plot(time, SystemStatePostFilter_mV, 'DisplayName', 'Filterd')
hold off
title(strcat(controllertype, ' Water Level Process Filter (', tuningmethod))
xlabel('Time [s]')
ylabel('Water Level [mV]')
legend
subplot(2, 1, 2)
plot(time, abs(SystemState_mV - SystemStatePostFilter_mV), 'DisplayName', '|Raw - Filtered|')
title(strcat(controllertype , ' Water Level Process Filter Removed Noise (' , tuningmethod))
xlabel('Time [s]')
ylabel('Measurment Noise [mV]')
legend
set(gcf, 'Position', get(0, 'Screensize'));
savefig(strcat('Plot_Filter_', destinationfileidentifier, '.fig'))
saveas(gcf, strcat('Plot_Filter_', destinationfileidentifier, '.png'))

figure(3)
subplot(4, 1, 1)
plot(time, Controller_P, 'DisplayName', 'P Part')
hold on % more plots in the same diagram
plot(time, Controller_I, 'DisplayName', 'I Part')
plot(time, Controller_D, 'DisplayName', 'D Part')
hold off
title(strcat(controllertype, ' Water Level Process Inside Controller (', tuningmethod))
xlabel('Time [s]')
ylabel('Outputsignal [mV]')
legend
subplot(4, 1, 2)
plot(time, Controller_P, 'DisplayName', 'P Part')
title(strcat(controllertype , ' Water Level Process Inside Controller (' , tuningmethod))
xlabel('Time [s]')
ylabel('P Part [mV]')
legend
subplot(4, 1, 3)
plot(time, Controller_I, 'DisplayName', 'I Part')
title(strcat(controllertype , ' Water Level Process Inside Controller (' , tuningmethod))
xlabel('Time [s]')
ylabel('I Part [mV]')
legend
subplot(4, 1, 4)
plot(time, Controller_D, 'DisplayName', 'D Part')
title(strcat(controllertype , ' Water Level Process Inside Controller (' , tuningmethod))
xlabel('Time [s]')
ylabel('D Part [mV]')
legend
set(gcf, 'Position', get(0, 'Screensize'));
savefig(strcat('Plot_Controller_Details_', destinationfileidentifier, '.fig'))
saveas(gcf, strcat('Plot_Controller_Details_', destinationfileidentifier, '.png'))
