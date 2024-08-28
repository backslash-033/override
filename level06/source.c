#include <stdio.h>

int auth(char *s, int key)
{
	int i;
	int res;
	int len;

	s[strcspn(s, "\n")] = 0;
	len = strnlen(s, 32);
	if (len <= 5)
		return 1;
	if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
	{
		puts("\x1B[32m.---------------------------.");
		puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1B[32m'---------------------------'");
		return 1;
	}
	else
	{
		res = (s[3] ^ 0x1337) + 0x5eeded;
		for (i = 0; i < len; ++i)
		{
			if (s[i] <= 31)
				return 1;
			res += (res ^ (unsigned int)s[i]) % 1337;
		}
		return key != res;
	}
}

int	main()
{
	int key;
	char s[28];

	puts("***********************************");
	puts("*\t\tlevel06\t\t	*");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(s, 32, stdin);

	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf(???, &key);

	if (auth(s, key))
		return 1;

	puts("Authenticated!");
	system("/bin/sh");
	return 0;
}