%% Creating the mex files
buildMex();
%% Generating keys
t1 = 0;
for i = 1:1000
    tic
    [pub_key_file, priv_key_file] = genecp_nistp256();
    t1 = t1 + toc;
end
fprintf('Mean time required to generate keys is : %fs\n', t1/1000)
%% Signing file with previous keys
file = 'file_to_sign.txt';
tic
[signature] = digital_signature(priv_key_file,file);
t2 = toc;
fprintf('Time required for signature is : %fms\n', t2*1000)
%% Verify signature
tic
verif_state = verify_signature(pub_key_file, file,signature);
t3 = toc;
fprintf('Time required to verify signature : %fms result = %i\n\n', t3*1000, verif_state);
%% Mean time verify signature
t3 = 0;
for i = 1:1000
    tic
    verify_signature(pub_key_file, file,signature);
    t3 = t3 + toc;
end

fprintf('Mean time required to verify signature is : %f ms\n', t3);
%% Ploting glabal parameters
fprintf("Total elapsed time is %fs\n", t1/1000+t2+t3/1000);
