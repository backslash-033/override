#include <stdio.h>

char a_user_name[100];

int verify_user_pass() {
	return (strcmp("admin", a_user_name));
}

int verify_user_name() {
	puts("verifying username....\n");
	return (strcmp("dat_wil", a_user_name));
}

int main(void) {
	int		ret_var;
	int		verify;
	char	password[64];
	
	memset(password, 0, 64);
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(&a_user_name, 0x100, stdin);
	verify = verify_user_name();
	if (verify == 0) {
		puts("Enter Password: ");
		fgets(password, 100, stdin);
		verify = verify_user_pass(password);
		if ((verify == 0) || (verify != 0)) {
			puts("nope,  incorrect password...\n");
			ret_var = 1;
		}
		else {
			ret_var = 0;
		}
	}
	else {
		puts("nope,  incorrect username...\n");
		ret_var = 1;
	}
	return ret_var;
}