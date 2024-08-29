#include <stdio.h>

int clear_stdin()
{
	char	result;

	do
		result = getchar();
	while (result != 10 && result != 0xFF);

	return result;
}

int get_unum()
{
	int res[3];

	res[0] = 0;
	fflush(stdout);
	scanf("%u", res);
	clear_stdin();
	return res[0];
}

int	store_number(int *data)
{
	unsigned int unum;
	unsigned int index;

	printf(" Number: ");
	unum = get_unum();
	printf(" Index: ");
	index = get_unum();
	if (index == 3 * (index / 3) || (unum & 0xff000000 == 0xb7000000))
	{
		puts(" *** ERROR! ***");
		puts("  This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return 1;
	}
	else
	{
		data[index] = unum;
		return 0;
	}
}

int	read_number(int *data)
{
	int unum;

	printf(" Index: ");
	unum = get_unum();
	printf(" Number at data[%u] is %u\n", unum, data[unum]);
	return 0;
}

int main(int argc, const char **argv, const char **envp)
{
	int		data[100];
	int		return_value;
	char	s[20];

	return_value = 0;
	bzero(s, 20);
	memset(data, 0, sizeof(data));
	while (*argv) {
		memset((void *)*argv, 0, strlen(*argv));
		++argv;
	}
	while (*envp) {
		memset((void *)*envp, 0, strlen(*envp));
		++envp;
	}
	puts(
		"----------------------------------------------------\n"
		"  Welcome to wil's crappy number storage service!   \n"
		"----------------------------------------------------\n"
		" Commands:                                          \n"
		"    store - store a number into the data storage    \n"
		"    read  - read a number from the data storage     \n"
		"    quit  - exit the program                        \n"
		"----------------------------------------------------\n"
		"   wil has reserved some storage :>                 \n"
		"----------------------------------------------------\n");

	while (1)
	{
		printf("Input command: ");
		return_value = 1;
		fgets(s, 20, stdin);
		s[strlen(s) - 1] = 0;
		if (!memcmp(s, "store", 5u))
		{
			return_value = store_number(data);
		}
		else if (!memcmp(s, "read", 4u))
		{
			return_value = read_number(data);
		}
		else if (!memcmp(s, "quit", 4u))
			return 0;

		if (return_value)
			printf(" Failed to do %s command\n", s);
		else
			printf(" Completed %s command successfully\n", s);

		bzero(s, 20);
	}
}