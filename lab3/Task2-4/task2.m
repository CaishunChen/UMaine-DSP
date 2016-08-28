%% Bandpass filter to meet specifications stated in Task 2 of Lab 3
% 
% Authors:  (ECE486 Group 10, Spring 2016)
%   Josh Scripture, Nabil Chowdhoury, Chris Eustis

%% Setup
close all;
clf;
clear; 

j = 1i;
N = 2^16;
w = linspace(0,.5,N);
z = exp(2*pi*j*w);

pole_order = 8;
zero_order = 8;

%% Poles and Zeros
poles=[   
    .3 * exp(2*pi*j* 0.1*[1 ;-1]);...
    .8 * exp(2*pi*j* 0.18*[1 ;-1]);...
    .8 * exp(2*pi*j* 0.23*[1 ;-1]);...
    .9 * exp(2*pi*j* 0.2*[1 ;-1]);...
    .9 * exp(2*pi*j* 0.23*[1 ;-1]);...
	.8 * exp(2*pi*j* 0.3*[1 ;-1])]; 

zeros=[
    1 * exp(2*pi*j* 0.01*[1 ;-1]);...
    1 * exp(2*pi*j* 0.05*[1 ;-1]);...
    1 * exp(2*pi*j* 0.01*[1 ;-1]);...
    1 * exp(2*pi*j* 0.02*[1 ;-1]);...
    1 * exp(2*pi*j* 0.44*[1 ;-1]);...
    1 * exp(2*pi*j* 0.655*[1 ;-1])];
  
%% Pole/Zero plot
figure(1); clf;
hold on;
zplane(poles, zeros)
grid on
title 'Pole-Zero Diagram'
hold off;

%% Calculate Filter - Create Transfer Function

% Set numerator and denominator
num_c = poly(zeros);
den_c = poly(poles);

% Evaluate zeros and poles
num = polyval(num_c,z);
den = polyval(den_c,z);

% Magnitude
H_f = abs(1*num./den);

%% Adjust Gain

pin_freq=.325;
pin_gain=10^(-40/20);

% Evaluate gain
index = find(w >= pin_freq, 1)
k = pin_gain / H_f(index)

% Magnitude with gain
H_f = abs(k*num./den);

%% Pass/Reject Band Boxes for Specifications
figure(2);hold;
plot(w,db(H_f));
h1=patch([0 0 .1 .1],[-90 -60 -60 -90],'r');
h2=patch([.15 .15 .25 .25],[-5 -3 5 3],'r');
h3=patch([.35 .35 .5 .5],[-90 -50 -50 -90],'r');
set(h1,'facealpha',.5);
set(h2,'facealpha',.5);
set(h3,'facealpha',.5);
% set(h4,'facealpha',.5);
grid on;
title 'Filter Gain'
xlabel 'Normalized Freq.'
ylabel 'Gain (dB)'
axis([0 0.5 -60 10])

%% Task 3
create_sos(zeros, poles, k);