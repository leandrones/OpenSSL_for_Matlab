%% Compiles mex files
buildMex();

%% Calculates average time as function of key size being generated
%curves = [ "secp224r1" , "prime256v1", "secp384r1" , "secp521r1" ];
curves = { 'secp224r1' , 'prime256v1' , 'secp384r1' , 'secp521r1' };
sizes = [ 224 , 256, 384, 521 ];
iteration_number = 100;
generating_times = zeros(1,4);
priv_key_file = 'files/testPrivKey.pem';
pub_key_file  = 'files/testPubKey.pem';

for i = 1:(length(curves))
    
    for j = 1:iteration_number
        tic
        genecp_nistp(curves{1,i},pub_key_file,priv_key_file);
        generating_times(1,i) =  generating_times(1,i) + toc;
    end

    generating_times(1,i) = generating_times(1,i)/iteration_number*1000;
end

% Plots key size x  average time

figure(1)
    plot(sizes,generating_times)
    xlabel("Key size in octets")
    ylabel("Time to generate keys (ms)")
    title("Average key generation time as function of key size")
    grid minor
    
