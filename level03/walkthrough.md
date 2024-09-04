# Level 03

This level is not about memory corruption, but about reverse engineering.
The program asks for a password (integer), if we have the right one, we get a shell.

```bash
level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password: 27

Invalid Password
```

Basically, the algorithm behind is this one:
- We have the base string "Q}|u`sfg~sf{}|a3"
- Every byte of the string going through the XOR operation
- The result has to match "Congratulations!", if it does, we have access to a shell.

So we just wrote a single program that does this very thing, for every bytes from 0 to 255.
The result is 18. So lets try:

```bash
level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:18

Invalid Password
```

Unfortunately it doesn't work. Why?
Because the key is calculated this way:
- `0x1337d00d - pass`

So we just have to input 0x1337d00d - 18 for this operation result to 18.

```bash
level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:322424827
$ whoami
level04
$ cd ../level04
$ cat .pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

## .pass: kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf