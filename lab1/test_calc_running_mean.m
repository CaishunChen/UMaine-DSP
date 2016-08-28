%% Test Script for the calc_running_mean function
% 
% Authors:  (ECE486 Group 10, Spring 2016)
%   Josh Scripture, Nabil Chowdhoury, Chris Eustis

%% Test 1
clc;
clear;

% Set sample size
samples = 10;

% x(n) = vector of data to average
x = sin(1:1000)+1;

% Set blocksize
blocksize = 4;

% Initialize struct with given sample size and blocksize
s = init_running_mean(samples, blocksize);

% Calculate running mean
[y,s] = calc_running_mean(x,s)
[y,s] = calc_running_mean(x,s)
[y,s] = calc_running_mean(x,s)
[y,s] = calc_running_mean(x,s)

% The resulting value, stored in the output y, should be hovering around one.

%% Test 2
clc;
clear;

% Set sample size
samples = 10;

% x(n) = vector of data to average
x = ones(1,1000);

% Set blocksize
blocksize = 4;

% Initialize struct with given sample size and blocksize
s = init_running_mean(samples, blocksize);
% Calculate running mean
[y,s] = calc_running_mean(x,s)
[y,s] = calc_running_mean(x,s)
[y,s] = calc_running_mean(x,s)
[y,s] = calc_running_mean(x,s)

% The average should, on the fifth run, become 1.

%% Test 3
clc;
clear;

% Set sample size
samples = 2;

% x(n) = vector of data to average
x = ones(1,1000);

% Set blocksize
blocksize = 2;

% Initialize struct with given sample size and blocksize
s = init_running_mean(samples, blocksize);
% Calculate running mean
[y,s] = calc_running_mean(x,s)
[y,s] = calc_running_mean(x,s)

% The output, y, should become averaged at 1 for the blocksize after the second sample.