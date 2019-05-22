%% Generating keys
t1 = 0;
for i = 1:1000
    tic 
    [pub_key_file, priv_key_file] = genecp_nistp256();
    t1 = t1 + toc;
end 
fprintf('Mean time required to generate keys is : %fs\n', t1/1000)
%% Signing file with previous keys
file = "file_to_sign.txt"
tic 
signed_file = digital_signature(priv_key_file, file);
t2 = toc;
fprintf('Time required for signature is : %fs\n', t2)
%% Verify signature
tic 
verif_state = verify_signature(pub_key_file, file,signed_file);
t3 = toc;
fprintf('Times required to verify signature : %fs\n\n', t3)
%% Ploting glabal parameters
fprintf("Total elapsed time is %fs", t1+t2+t3)
