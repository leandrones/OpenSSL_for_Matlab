%% Compiling Mex Files
buildMex();
%% Choose EC Curve
[curve, pub_key_file, priv_key_file] = menu_chose_function();
%% Generating keys
genecp_nistp(curve, pub_key_file, priv_key_file);
%% Signing file with previous keys
file = 'files/1.txt';
sigfile = 'files/1.bin';
digital_signature(priv_key_file,file,sigfile);
%% Verify signature
verif_state = verify_signature(pub_key_file, file, sigfile);
fprintf('Verification state = %d\n',verif_state)
