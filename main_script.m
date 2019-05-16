%% Generating keys
tic 
[priv_key, pub_key] = genecp_nistp256();
t1 = toc;
fprintf('Time required to generate keys is : %fs', t1)
%% Signing file with previous keys
file = importdata(file_to_sign.txt);
tic 
[signature] = digital_signature(priv_key, file);
t2 = toc;
fprintf('Time required for signature is : %fs', t2)
%% Verify signature
tic 
verif_state = verif_signature(pub_key, file);
t3 = toc;
fprintf('Times required to verify signature : %fs\n\n', t3)
%% Ploting glabal parameters
fprintf("Total elapsed time is %fs", t1+t2+t3)
