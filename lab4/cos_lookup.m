clear; clc;
m = 9;
N = 2^m;    % 512
k = 0:1:N-1;
% x = 0:1/N:pi;
y = cos(2*pi*(k/N));

fprintf('#define LUT[%d] = {', size(y,2));
for i=1:size(y,2)-1
    fprintf('%f, ', y(i));
    if (mod(i,10) == 0)
        fprintf('\n\t\t');
    end
end
fprintf('%f};', y(size(y,2)));