gen: genecp_nistp256_versionC.c
	gcc genecp_nistp256_versionC.c -o genecp_nistp256_versionC -lssl -lcrypto -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include
verif: verify_signature_versionC.c
	gcc verify_signature_versionC.c -o verify_signature_versionC -lssl -lcrypto -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include
sign: digital_signature_versionC.c
	gcc digital_signature_versionC.c -o digital_signature -lssl -lcrypto -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include

sign_size: digital_signature_filesize_versionC.c
	gcc digital_signature_filesize_versionC.c -o digital_signature_filesize -lssl -lcrypto -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include

verify_size: verify_signature_filesize_versionC.c
	gcc verify_signature_filesize_versionC.c -o verify_signature_filesize -lssl -lcrypto -L/usr/local/opt/openssl/lib -I/usr/local/opt/openssl/include
