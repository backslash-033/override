#include <stdio.h>

typedef struct data {
	char	msg[140];
	char	usr[40];
	int	msg_length;
}	data;

int secret_backdoor()
{
	char s[128];

	fgets(s, 128, stdin);
	return system(s);
}

char *set_msg(data *d)
{
	char s[1024];

	memset(s, 0, sizeof(s));
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(s, 1024, stdin);
	return strncpy(d->msg, s, d->msg_length); // last arg 140 ?
}

int set_username(data *d)
{
	char s[140];
	int i;

	memset(s, 0, 0x80uLL);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(s, 128, stdin);
	for (i = 0; i <= 40 && s[i]; ++i)
		d->usr[i] = s[i];
	return printf(">: Welcome, %s", (const char *)(d->usr));
}

int handle_msg()
{
	data	d;

	d.msg_length = 140;
	set_username(&d);
	set_msg(&d);
	return puts(">: Msg sent!");
}

int main(int argc, const char **argv, const char **envp)
{
	puts(
		"--------------------------------------------\n"
		"|   ~Welcome to l33t-m$n ~    v1337        |\n"
		"--------------------------------------------");
	handle_msg();
	return 0;
}