%% Compiling Mex Files
buildMex();
%% Choose EC Curve
[curve, pub_key_file, priv_key_file] = menu_chose_function();
%% Generating keys
tic
genecp_nistp(curve, pub_key_file, priv_key_file);
t1 = toc;
fprintf('Mean time required to generate keys is : %fs\n', t1)
%% Signing file with previous keys
file = './files/1.txt';
sigfile = './files/1.txt.sha256';
tic
digital_signature(priv_key_file,file,sigfile);
t2 = toc;
fprintf('Time required for signature is : %fms\n%s\n', t2*1000,sigfile);
%% Verify signature
tic
verif_state = verify_signature(pub_key_file, file, sigfile);
t3 = toc;
fprintf('Time required to verify signature : %fs result = %i\n\n', t3, verif_state);
%%
%Mean time verify signature
t3 = 0;
for i = 1:1000
    tic
    digital_signature(priv_key_file, file,sigfile);
    t3 = t3 + toc;
end
t3 = t3/1000;
fprintf('Mean time required to sign is : %fs\n', t3);
%% Ploting glabal parameters
fprintf("Total elapsed time is %fs\n", t1/1000+t2+t3/1000);
