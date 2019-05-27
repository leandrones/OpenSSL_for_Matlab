function [curve, pub_key_file, priv_key_file] = menu_chose_function()
doagain = true;
while doagain
  [option, curve, pub_key_file, priv_key_file] = makemenu();
  if option > 0
      doagain = false;
  end
end
end

function [option, curve, pub_key_file, priv_key_file] = makemenu()
option = menu('Choose Nist-p length',...
    'P-224',...
    'P-256',...
    'P-384',...
    'P-521');
switch option
    case 1
        curve = 'secp224r1';
        pub_key_file = 'PublicKey224.pem';
        priv_key_file = 'PrivateKey224.pem';
    case 2
        curve = 'prime256v1';
        pub_key_file = 'PublicKey256.pem';
        priv_key_file = 'PrivateKey256.pem';
    case 3
        curve = 'secp384r1';
        pub_key_file = 'PublicKey384.pem';
        priv_key_file = 'PrivateKey384.pem';
    case 4
        curve = 'secp521r1';
        pub_key_file = 'PublicKey521.pem';
        priv_key_file = 'PrivateKey521.pem';
end
end