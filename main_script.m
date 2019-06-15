%% Compiling Mex Files
buildMex();
%% Choose EC Curve
[curve, pub_key_file, priv_key_file] = menu_chose_function();
%% Generating keys
T1 = ones(1,1000);
for i = 1:1000
    tic
    genecp_nistp(curve, pub_key_file, priv_key_file);
    T1(i) = toc;
end
fprintf('Mean time required to generate keys is : %fms\n', sum(T1)/10)
%% Loading C data 
% gendata = csvread('genData.txt');
% plot(1:1000,T*1000)
% hold on
% plot(1:1000,gendata(1:1000));
%mean(T*1000)
%mean(gendata)
%% Signing file with previous keys
file = './files/1.txt';
sigfile = './files/1.txt.sha256';
T2 = ones(1,1000);
for i = 1:1000
    tic
    digital_signature(priv_key_file,file,sigfile);
    T2(i) = toc;
end
fprintf('Time required for signature is : %fms\n%s\n', sum(T2),sigfile);
file = 'files/1.txt';
sigfile = 'files/1.txt.sha256';
tic
digital_signature(priv_key_file,file,sigfile);
t2 = toc;
fprintf('Time required for signature is : %fms\n%s\n', t2*1000,sigfile);
%% Verify signature
T3 = ones(1,1000);
for i = 1:1000
    tic
    verif_state = verify_signature(pub_key_file, file, sigfile);
    T3(i) = toc;
end
fprintf('Time required to verify signature : %fs ms result = %i\n\n', sum(T3), verif_state);
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
%fprintf("Total elapsed time is %fs\n", t1/1000+t2+t3/1000);

%% Plotting data

% x = 1:1000;
% plot(x,1000*T1)
% title('Comparison of key generation time for key size of 256 bits')
% xlabel('Iteration')
% ylabel('Time in ms')
% hold on
% % C file to load
% data = csvread('./data/.....txt');
% plot(x,data)

% hold off