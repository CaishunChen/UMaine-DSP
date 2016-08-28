function [y,s] = calc_running_mean(x, s)
%CALC_RUNNING_MEAN Running average of samples. 
%   [y,s] = calc_running_mean(x, s) takes an input signal x of blocksize 
%   samples and averages them over samples size. The structure s holds the
%   data necessary for doing the calculation. The result is stored in the structure
%   under the variable y.

% Author: Josh Scripture, Nabil Chowdhoury, Chris Eustis
% ECE 486 - Lab 1
% February 5, 2016

% Fill block
for i=1:s.blocksize
    s.block(i)=x(s.j+i);
end

% Bring block into circular summing array and re-evaluate average
for i=1:s.blocksize
    q=s.lastM(mod(i+s.j-1,s.M)+1);
    s.lastM(mod(i+s.j-1,s.M)+1)=s.block(i);
    
    if i==1
        s.y(i)=s.y(s.blocksize)+s.block(i)/s.M-q/s.M;
    else
        s.y(i)=s.y(i-1)+s.block(i)/s.M-q/s.M;
        
    end
end
s.j=s.j+s.blocksize;
y=s.y;

