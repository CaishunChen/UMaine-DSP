%% FFT Analysis of Periodic Signals
% 
% Authors:  (ECE486 Group 10, Spring 2016)
%   Josh Scripture, Nabil Chowdhoury, Chris Eustis

clear
close all

read = csvread('data.csv');

% Describe in input signal
A0 = 19.4;
f0 = 0.3074;
theta0 = 0.1234;
A1 = 0.2;
f1 = 0.33;
theta1 = 0.5678;
%A0 = 12.3;
%f0 = 0.3074;
%theta0 = 0.1234;
%A1 = 0.5;
%f1 = 0.33;
%theta1 = 0.5678;

% Number of values around unit circle for the FFT
N1 = 1024;
n = 0:N1-1;

% Input signal
% t = A0*cos(2*pi*f0*n+theta0) + A1*cos(2*pi*f1*n+theta1);
%x = A0*cos(2*pi*f0*n+theta0) + A1*cos(2*pi*f1*n+theta1);
x=csvread('data.csv')

% Plot a stem of the input
% figure(1); clf;
% stem(n,t);
% grid on;
% xlabel('Values, N');
% ylabel('Amplitude');

% Calculate FFT of input signal
X = fft(x);
f = (0:1023)/1024;

% Plot the FFT as a stem
figure(2);clf;
% stem(f, abs(t), '.');
grid on;
xlabel('Normalized Frequency');
ylabel('Magnitude');
hold on;


% Number of values around unit circle for the FFT
N2 = 64*1024;
X2 = fft(read, N2);
% Plot a second FFT with different number of values
f2 = (0:N2-1)/N2;
plot(f2,abs(X2));
grid on;

% Compare answer
% Take highest point, divide by 512*2 = 6482/512*2 = 25.302 --> Close to A0

% Amplitude of A0
fprintf('A0: %f\n', max(abs(X2))/N1*2);

% Amplitude of A1
% fprintf('A1: %f\n', max(abs(X2))/N2*2);

% Plot window function
figure(3); clf;
beta = 5;
% Define window
w = kaiser(1024, beta)';
X3 = fft(read.*w, N2);
plot(f2, 20*log10(abs(X3)));
grid on;
xlabel('Normalized Frequency');
ylabel('Magnitude');


% Find amplitude here
figure(4); clf;
plot(f2, abs(X3));
grid on;
xlabel('Normalized Frequency');
ylabel('Magnitude');