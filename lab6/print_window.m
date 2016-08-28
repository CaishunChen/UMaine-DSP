%% Kaiser Window Generation
% 
% Authors:  (ECE486 Group 10, Spring 2016)
%   Josh Scripture, Nabil Chowdhoury, Chris Eustis

clear;
close all;

%% Print out kaiser window array for C implementation
% Define FFT Length
fftLen = 1024;
% Define beta for Kaiser window
beta = 8.0;

% Generate array for window function
window = kaiser(fftLen, beta);

% Print out the array to easily place in C file
fprintf('float32_t window[%d] = {', fftLen*2);
for i = 1: fftLen
    if (mod(i, 10) == 0)
        fprintf('\n\t\t    ')
    end
    if (i == fftLen)
        fprintf('%f, ', window(i));
        fprintf('%f};', window(i));
    else
        fprintf('%f, ', window(i));
        fprintf('%f, ', window(i));
    end
    i+1;
end
