#include <stdio.h>

int main(void) {
	int last_cmp;
	size_t len;
	char password [112];
	char pass_content [48];
	char username [96];
	int pass_len;
	FILE *file_pass;

	bzero(password,  sizeof(password));
	bzero(pass_content,  sizeof(pass_content));
	bzero(username,  sizeof(username));

	file_pass = fopen("/home/users/level03/.pass", "r");
	if (file_pass == NULL) {
		fwrite("ERROR: failed to open password file\n", 1, 0x24, stderr);
										/* WARNING: Subroutine does not return */
		exit(1);
	}

	len = fread(pass_content, 1, 0x29, file_pass);
	pass_len = (int)len;
	len = strcspn(pass_content, "\n");
	pass_content[len] = '\0';
	if (pass_len != 0x29) {
		fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 0x24, stderr);
										/* WARNING: Subroutine does not return */
		exit(1);
	}

	fclose(file_pass);
	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");

	printf("--[ Username: ");
	fgets(username, 100, stdin);
	len = strcspn(username, "\n");
	username[len] = '\0';

	printf("--[ Password: ");
	fgets(password, 100, stdin);
	len = strcspn(password, "\n");
	password[len] = '\0';

	puts("*****************************************");
	last_cmp = strncmp(pass_content, password, 0x29);
	if (last_cmp == 0) {
		printf("Greetings,  %s!\n", username);
		system("/bin/sh");
		return 0;
	}

	printf(username);
	puts(" does not have access!");
	exit(1);
}