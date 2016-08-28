function s = init_running_mean(M, blocksize);
%INIT_RUNNING_MEAN Initialize structure for calculating the running average of a signal. 
%   s = init_running_mean(M, blocksize) takes a sample size M and a
%   blocksize value to initialize a structure used to calculate the running
%   average of an input signal. The necessary data to perform the
%   calculations are stored in this structure as the return value.

% Author: Josh Scripture, Nabil Chowdhoury, Chris Eustis
% ECE 486 - Lab 1
% February 5, 2016

% Initiliaze output to zeros and store blocksize and sample size
s = struct('lastM',zeros(1,M),'block', zeros(1,blocksize), 'y', zeros(1,blocksize), 'blocksize', blocksize, 'M', M, 'j', 0);