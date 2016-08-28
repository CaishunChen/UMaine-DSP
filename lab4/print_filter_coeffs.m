% Used for producing C output for use in IIR filter
% Must have used fdatool, export data into G and SOS variables else this
% will fail
g = 1;
for i=1:size(G,1)
    g = g * G(i,1);
end

fprintf('\tfloat g = %f;\n', g);

index = 0;
for i=1:size(SOS,1)
    for j=1:6
        if (j ~= 4)
            fprintf('\tbiquad_coefs[%d] = %f;\n', index, SOS(i,j));
            index = index + 1;
        end
    end
end
