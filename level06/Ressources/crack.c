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
	res = (s[3] ^ 0x1337) + 0x5eeded;
	for (i = 0; i < len; ++i)
	{
		if (s[i] <= 31)
			return 1;
		res += (res ^ (unsigned int)s[i]) % 1337;
	}
	printf("\033[32mres: [%d]\033[0m\n", res);
	return key != res;
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
	scanf("%u", &key);

	if (auth(s, key))
		return 1;

	puts("Authenticated!");
	system("/bin/sh");
	return 0;
}