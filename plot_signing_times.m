%% Compiling Mex Files
buildMex();
%% Choose EC Curve
[curve, pub_key_file, priv_key_file] = menu_chose_function();
%% Generating keys
tic
genecp_nistp(curve, pub_key_file, priv_key_file);
t1 = toc;
%%
N = 50
signing_times = zeros(1,N);
verifying_times = zeros(1,N);
signing_sizes = 1:N;
average_repetitions = 1000

%% Signature average times
for i = 1:N
    file = strcat('files/',rptgen.toString(i),'.txt');
    signature = strcat('files/',rptgen.toString(i),'.bin');
    tic
    for j = 1:average_repetitions
	      digital_signature(priv_key_file,file,signature);
    end
    signing_times(1,i) = toc/average_repetitions;
end

%% Verification average times
for i = 1:N
    file = strcat('files/',rptgen.toString(i),'.txt');
    signature = strcat('files/',rptgen.toString(i),'.bin');
    tic
    for j = 1:average_repetitions
        verif_state = verify_signature(pub_key_file,file,signature);
    end
	verifying_times(1,i) = toc/average_repetitions;
end

%%
figure(1)
subplot(2,1,1)
    plot(signing_sizes,signing_times);
    xlabel('Size of file (MB)')
    ylabel('Time to sign (s)')
    title('Time to sign a file as function of file size')
    grid minor
subplot(2,1,2)
    plot(signing_sizes, verifying_times);
    xlabel('Size of file (MB)')
    ylabel('Time to verify (s)')
    title('Time to verify a file as function of file size')
    grid minor
    
    
    
