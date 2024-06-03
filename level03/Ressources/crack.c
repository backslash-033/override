#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*XOR(char *s, int k) {
	char *res = strdup(s);

	for (int i = strlen(s); i + 1 != 0; i--) {
		res[i] = res[i] ^ k;
	}

	return res;
}

int main() {
	unsigned char key = 0;

	for (; key != 0xff; key++) {
		char *xored = XOR("Q}|u`sfg~sf{}|a3", key);
		if (xored[0] == 'C') {
			printf("%d: %s %s\n", key, xored, "Congratulations!");
			printf("%d\n", 0x1337d00d - key);
		}
		free(xored);
	}
}