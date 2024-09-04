# Level 00

When launching the executable, we are asked to prompt a password.

```bash
level00@OverRide:~$ ./level00
***********************************
*            -Level00 -           *
***********************************
Password: I have no clue

Invalid Password!
```

By looking at the assembly, we can see that `scanf()` wants an int as an imput.
We also see that this int is compared to `0x149c`, or 5276 in decimal.

```gdb
(gdb) disas main
Dump of assembler code for function main:
[...]
   0x080484ce <+58>:    mov    eax,0x8048636
   0x080484d3 <+63>:    lea    edx,[esp+0x1c]
   0x080484d7 <+67>:    mov    DWORD PTR [esp+0x4],edx
   0x080484db <+71>:    mov    DWORD PTR [esp],eax
   0x080484de <+74>:    call   0x80483d0 <__isoc99_scanf@plt>
   0x080484e3 <+79>:    mov    eax,DWORD PTR [esp+0x1c]
   0x080484e7 <+83>:    cmp    eax,0x149c
[...]
End of assembler dump.
(gdb) x/s 0x8048636
0x8048636:       "%d"
```

```bash
Invalid Password!
level00@OverRide:~$ ./level00 
***********************************
*            -Level00 -           *
***********************************
Password: 5276

Authenticated!
$ cd ../level01
$ cat .pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```