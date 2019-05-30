%% Choose EC Curve
[curve, pub_key_file, priv_key_file] = menu_chose_function();
%%
genecp_nistp(curve, pub_key_file, priv_key_file);
curve
signing_times = zeros(1,100);
verifying_times = zeros(1,100);
signing_sizes = linspace(1,100);

%%
for i = 1:100
    file = strcat('files/',rptgen.toString(i),'.txt');
    signature = strcat('files/',rptgen.toString(i),'.sha256');
    %file = 'testfile.txt'
    tic
    [signature] = digital_signature(priv_key_file,file,signature);
    signing_times(1,i) = toc; 
    tic
    verif_state = verify_signature(pub_key_file,file,signature)
    verifying_times(1,i) = toc;
end

figure(1)
    plot(signing_sizes,signing_times);
    xlabel('Size of file (MB)')
    ylabel('Time to sign (s)')
    title('Time to sign a file as function of file size')
    grid minor
    
figure(2)
    plot(signing_sizes, verifying_times);
    xlabel('Size of file (MB)')
    ylabel('Time to verify (s)')
    title('Time to verify a file as function of file size')
    grid minor
    