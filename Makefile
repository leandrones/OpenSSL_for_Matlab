verif: verify_signature.c
	gcc verify_signature.c -o verify_signature -lssl -lcrypto
sign: digital_signature.c
	gcc digital_signature.c -o digital_signature -lssl -lcrypto