function buildMex(enblDbg)
    %   Examples:
    %       buildMex    Defaults to false
    %       buildMex(true) or buildMex(false)
    %
    %   Takes:
    %       enblDbg:   Enable Debug mode (defaults false)
    %
    %   Notes:
    %       false has no debugging symbols (DEFAULT)
    %       true has debugging symbols
    %
    %   Author:
    %       Anthony Gabrielson (adapted by Leandro Nascimento)
    
   
    
    if ~exist('enblDbg','var') || isempty(enblDbg),enblDbg=false; end
    
    filenames = dir('*.c*');
    
    options = '';
    if(enblDbg)
       options = [options ' -g ']; 
    end
    
    if(ispc()) 
        fprintf(1,'Building PC...\n');
        options = [' C:\openssl\lib\libeay32.lib -IC:\openssl\include ' options];
    elseif(ismac())
        fprintf(1,'Building Mac...\n');
        options = [options ' -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include -lssl -lcrypto '];
    elseif(isunix())
        fprintf(1,'Building UNIX...\n');
        options = [options ' -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include -lssl -lcrypto '];
    end
    
    for J=1:length(filenames)
        cmd = ['mex ' filenames(J).name options];
        eval(cmd);
    end