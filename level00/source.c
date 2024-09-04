int main() {
	int	pass;
	puts("***********************************");
	puts("*            -Level00 -           *");
	puts("***********************************");
	printf("Password:");

	scanf("%d\n", &pass);

	if (pass == 5276) {
		execl("/bin/sh", NULL);
	} else {
		puts("Invalid Password!");
	}
}