# Level 06

This level may seem complicated at first, but it's really simple.

Basically, we are faced with an encription algorithm that checks if a string is
compatible with a key, both are our inputs. The string need to be more than 5
characters and must only contain printable characters.

```c
for (i = 0; i < len; ++i)
{
	if (s[i] <= 31)
		return 1;
	res += (res ^ (unsigned int)s[i]) % 1337;
}
return key != res;
```

The problem with this code, is that it lets the result in a variable.
When reversed, we can simply re-write the code and put a `printf()` to show us 
what's inside the variable that we want to compare it with.

```c
for (i = 0; i < len; ++i)
{
	if (s[i] <= 31)
		return 1;
	res += (res ^ (unsigned int)s[i]) % 1337;
}
printf("\033[32mres: [%d]\033[0m\n", res);
return key != res;
```

Now I just need to recompile and lunch my own executable to know which key matches
with any given string.

```bash
$> ./test
***********************************
*               level06                 *
***********************************
-> Enter Login: You shall not pass!
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: l
res: [6238196]
```

And use this result on the real executable file.

```bash
level06@OverRide:~$ ./level06 
***********************************
*               level06           *
***********************************
-> Enter Login: You shall not pass!
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6238196
Authenticated!
$ whoami
level07
$ cd ../
$ cd level07
$ cat .pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```