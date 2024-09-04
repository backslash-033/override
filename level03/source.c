int decrypt(unsigned char key) {
	int ret_value;
	char *congrats;
	char encrypted[17];

	strpcy(encrypted, "Q}|u`sfg~sf{}|a3");
	for (int i = strlen(encrypted); i + 1 != 0; i--) {
		encrypted[i] = encrypted[i] ^ key;
	}
	congrats = (char *)"Congratulations!";
	if (strcmp(encrypted, congrats)) {
		ret_value = system("/bin/sh");
	}
	else {
		ret_value = puts("\nInvalid Password");
	}
	return ret_value;
}

int	test(int a, int b) {
	int res;

	res = b - a;
	switch(res) {
		case 0x1:
		case 0x2:
		case 0x3:
		case 0x4:
		case 0x5:
		case 0x6:
		case 0x7:
		case 0x8:
		case 0x9:
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x15:
			decrypt(res);
			break;
		default:
			decrypt(rand());
			break;
	}
	return;
}

int main(void) {
	int seed;
	int	pass;

	seed = time(0x0);
	srand(seed);
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	__isoc99_scanf("%d", &pass);
	test(pass, 0x1337d00d);
	return 0;
}