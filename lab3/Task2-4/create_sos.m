function create_sos(zeros, poles, k)
%create_sos Create output values to be used in C program. 
%   create_sos(zeros, poles, k) takes the input of zeros of poles
% of the transfer function, as well as the filter gain, to produce the
% outputs usable for direct placement into the C program in which to
% test the filter.

% Author: Josh Scripture, Nabil Chowdhoury, Chris Eustis
% ECE 486 - Lab 3
% March 18, 2016

% Take poles and zeros and convert to second-order sections model
% sos contains the coefficients of which need to be printed out as an array
% g is the overall gain of the system
[sos,g]=zp2sos(zeros,poles,k,'down');

fprintf('BIQUAD_T *filt;\n')
fprintf('int sections = 4;\n')
fprintf('float g = %d;\n',g);

% Print out an array of the coefficients
ind = 0;
for i = 1:size(sos,1)
    for j = 1:size(sos,2)
        fprintf('biquad_coefs[%d] = %.10f;\n', ind, sos(i,j))
        ind = ind + 1;
    end
end