%% FIR Filter Design
% 
% Authors:  (ECE486 Group 10, Spring 2016)
%   Josh Scripture, Nabil Chowdhoury, Chris Eustis

clear;
close all;

%% Lowpass Filter

% (FFT Size for window method) Choose value of N - much larger than filter order than what will end up
N = 8 *1024;

% Figure out how index into FFT array translates to discrete-time
% frequencies
% f = k/n k=0,1,...,N-1
% May be off just a hair and conjugate symmetry may be wrong by just a
% little bit
f = (0:N-1)/N;

% Move values of frequencies just calculated, start at just halfway through
% the array and transfer them to left of the origin to get negative
% frequency that it really is (instead of 0.7, it is -0.3)
f(N/2+1+1:end) = f(N/2+1+1:end)-1;

% Guess a filter order - higher than what we think it will be and then
% reduce it down
M = 145;

% Guess something between 5-10 for cheby
% Adjust this to change where ripples are on transition band to end of
% attenuation
beta = 8.3;

% Create patches showing filter spec
figure(1); clf;
patch([0 .15 .15 0], [-60 -60 -100 -100],0.9*[1 1 1]);
patch([.25 .18 .18 .25], [10.25 10.25 9.75 9.75],0.9*[1 1 1]);
hold on;
% patch([.25 .15 .15 .25], [5.2 0.2 0.2 4.8],0.9*[1 1 1]);
% patch([.4 .5 .5 .4], [-100 -100 -60 -60],0.9*[1 1 1]);
% patch([.2 .25 .25 .2], [-1 -1 1 1],0.9*[1 1 1]);
patch([.28 .5 .5 .28], [-100 -100 -60 -60],0.9*[1 1 1]);

% Set up real transfer function to meet passband areas
% Need to make sure symmetric, so take absolute values of f
% Change this values to move where transitions occur
Hr1 = (abs(f) > 0.1682 & abs(f) < 0.2616).* 10.^(10/20);% 0 dB
% Hr2 = (abs(f) > 0.35 & abs(f) < 0.40).* 10.^(-8/20).*10.^(160.*(-abs(f)+.45)/20);
Hr=Hr1;

% Set up desired function - shows symmetry over 100
Hd = Hr.*exp(-j*2*pi*f*(M-1)/2);

% Plot the real transfer function
% plot(f, 20*log10(abs(Hr)), '.')
% Change x-axis to (-0.5, 0.5) to show Linear Phase (symmetry)
axis([0 0.5 -90 15]);
grid on;
xlabel('Normalized Frequency');
ylabel('Magnitude [dB]');

% Calculate Inverse FFT of desired function
hd = ifft(Hd);

% Final design (kaiser = window function)
h = hd(1:M).*kaiser(M, beta)';
% hold on;
% stem(0:M-1, h, 'r.');

plot(f, 20*log10(abs(fft(h,N))));

% Show linear phase impulse response
% figure(2); clf;
% stem(0:N-1, hd, '.');
% axis([0 M min(hd) max(hd)]);
% grid on;
% xlabel('Sample, M');
% ylabel('Impulse Magnitude');

fprintf('M = %d\n', M);
% print out array of coefficients
for i=1:M
    fprintf('h[%d] = %f;\n', i-1, h(i));
end