%% IIR Filter Design
% 
% Authors:  (ECE486 Group 10, Spring 2016)
%   Josh Scripture, Nabil Chowdhoury, Chris Eustis

clear;
close all;

% %% Lowpass filter
% 
% % Sampling Frequency
% Fs = 50000;
% 
% % Passband
% pb = 0.05*pi/pi;
% 
% % Stopband
% sb = 0.11*pi/pi;
% 
% % Passband Ripple (dB)
% % (0.9 = +-1 dB, 0.8 = +-2 dB, ...)
% pb_rip = -20*log10(0.99);
% 
% % Stopband Attenuation (dB)
% % (0.01 = 40 dB, .001 = 60 dB, ...)
% sb_atten = -20*log10(0.0001);
% 
% % Find IIR Filter order and natural frequency
% [N_Ellip, Ws_Ellip] = ellipord(pb, sb, pb_rip, sb_atten);
% 
% % Calculate coefficients
% [B_Ellip, A_Ellip] = ellip(N_Ellip, pb_rip, sb_atten, Ws_Ellip);
% 
% % Get patches to show specifications
% figure(1); clf;
% patch([0 .07 .07 0], [0.1 0.1 -0.1 -0.1],0.9*[1 1 1]);
% hold on;
% patch([.11 .5 .5 .11], [-100 -100 -80 -80],0.9*[1 1 1]);
% 
% % Plot it out
% [H_Ellip, W_Ellip]= freqz(B_Ellip, A_Ellip, Fs);
% plot(W_Ellip / pi, 20*log10(abs(H_Ellip)));
% axis([0 0.5 -90, 5]);
% ylabel('Magnitude [dB]');
% xlabel('Normalized Frequency');
% grid on;
% 
% % Print out filter design order
% fprintf('Lowpass Filter Order: %d\n', N_Ellip);

%% Bandpass filter

% Passband: 12 kHz to 15 kHz (9.9dB - 10.1 dB)
% Stopband: < 11.2 kHz (-60 dB)
% Stopband: > 16 kHz (-60 dB)

% Sampling Frequency
Fs = 48000;

% Passband
pass1 = 12000;
pass2 = 15000
gain = 10^(10.25/20); % 10 dB
% Stopband
stop1 = 11200;
stop2 = 16000;

% Normalize the frequencies
% Passband
% pb = [ 0.4*pi 0.6*pi]/pi;
% pb = [ pass1 pass2 ] / Fs;
pb = [ 0.18 0.25];

% Stopband
% stopband = [ 0.2*pi 0.8*pi]/pi;
% sb = [ stop1 stop2 ] / Fs;
sb = [0.15 0.28];

% Passband Ripple (dB)
% (0.9 = +-1 dB, 0.8 = +-2 dB, ...)
pb_rip = -20*log10(0.95);

% Stopband Attenuation (dB)
% (0.01 = 40 dB, .001 = 60 dB, ...)
sb_atten = -20*log10(0.0003);

% Find IIR Filter order and natural frequency
[N_Ellip, Ws_Ellip] = ellipord(pb, sb, pb_rip, sb_atten);

% Calculate coefficients
[B_Ellip, A_Ellip] = ellip(N_Ellip, pb_rip, sb_atten, Ws_Ellip*2);

% Get patches to show specifications
figure(2); clf;
patch([pb(1) pb(2) pb(2) pb(1)], [10.25 10.25 9.75 9.75],0.9*[1 1 1]);
hold on;
patch([0 sb(1) sb(1) 0], [-60 -60 -100 -100],0.9*[1 1 1]);
patch([.5 sb(2) sb(2) .5], [-60 -60 -100 -100],0.9*[1 1 1]);

% Add Gain
B_Ellip = B_Ellip*gain;

% Get frequency response
[H_Ellip, W]= freqz(B_Ellip, A_Ellip, Fs);

% Plot it out
plot((W / (2*pi)), 20*log10(abs(H_Ellip)));
axis([0 0.5 -80, 20]);
ylabel('Magnitude [dB]');
xlabel('Normalized Frequency');
grid on;

% Compute group delay
% Gd is group delay, W is frequencies (in radians) at which it is
% evaluated
[Gd, W] = grpdelay(B_Ellip, A_Ellip, Fs/2);

% Normalize W to 0 to 1, 
W_norm = W / (pi);

% Plot the group delay
% figure(3);
% h = plot(W_norm,Gd);
% xlim([0 .5]);
% xlabel('Normalized Frequency');
% ylabel('Samples of delay');
% grid on;

% Print out filter design order
fprintf('Bandpass Filter Order: %d\n', N_Ellip*2);