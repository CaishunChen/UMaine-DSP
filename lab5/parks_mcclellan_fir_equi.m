%% Parks-McClellan Equirippe FIR Filter Design
% Provided by Dr. Hummels

%% Example filter
clc; clear;
% Passband: Gain = 12 dB +/- 0.25 dB, 0.15 < f < 0.25
% Stopbands: 70 dB min Attenuation, f < 0.125 or 0.28 < f < 0.5

% Filter coefficients - adjust to meet spec!
M = 120;

% Passband gain
pass_gain = 12;
pass_gain_tolerance = 0.25;

% Passband corners
pass1 = 0.15;
pass2 = 0.25;

% Stopband corners
stop1 = 0.125;
stop2 = 0.28;

% Stopband attenuation
stop_atten = 70;

% Desired respone: Spec out three separate bands by giving the corner
% frequencies and gains at those corner frequencies. (Frequencies are
% normalized by Fs/2). Gains are absolute values (not dB)!
A1 = 10^(pass_gain/20)     % Passband Gain
F = [0 stop1 pass1 pass2 stop2 0.5] / 0.5      % Corner frequencies (0.5 = Fs/2)
A = [0 0     A1    A1    0     0  ];           % Corner frequency gains

% Weight vector designed so that each bands has its own tolerance
d1 = 10^(pass_gain/20) - 10^((pass_gain-pass_gain_tolerance)/20);       % Max passband error
d2 = 10^(-stop_atten/20);                                               % Max stopband error
W = [ 1/d2 1/d1 1/d2 ];         % ONE weight per specified band

% Filter design
h = firpm(M-1, F, A, W);

% Plot it...
figure(1); clf;

% Patches (shouldn't have to change if bandpass filter)
patch([0 stop1 stop1 0], [-stop_atten -stop_atten -100 -100],0.9*[1 1 1]);
hold on;
patch([stop2 0.5 0.5 stop2], [-stop_atten -stop_atten -100 -100],0.9*[1 1 1]);
patch([pass2 pass1 pass2 pass1], [(pass_gain+pass_gain_tolerance) (pass_gain+pass_gain_tolerance) (pass_gain-pass_gain_tolerance) (pass_gain-pass_gain_tolerance)],0.9*[1 1 1]);

% Not sure how to plot it yet...