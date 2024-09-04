#include <stdio.h>

unsigned int log_wrapper(FILE *a1, const char *notice, const char *file_name)
{
	char dest[264];

	strcpy(dest, notice);
	snprintf(&dest[strlen(dest)], 254 - strlen(dest), file_name);
	dest[strcspn(dest, "\n")] = 0;
	fprintf(a1, "LOG: %s\n", dest);
}

int main(int argc, const char **argv, const char **envp)
{
	FILE *v4;
	FILE *stream;
	int fd;
	char file_buff;
	char dest[104];

	file_buff = -1;
	if (argc != 2)
		printf("Usage: %s filename\n", *argv);
	v4 = fopen("./backups/.log", "w");
	if (!v4)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(v4, "Starting back up: ", argv[1]);
	stream = fopen(argv[1], "r");
	if (!stream)
	{
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}
	strcpy(dest, "./backups/");
	strncat(dest, argv[1], 99 - strlen(dest));
	fd = open(dest, 193, 432LL);
	if (fd < 0)
	{
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(1);
	}
	while (1)
	{
		file_buff = fgetc(stream);
		if (file_buff == -1)
			break;
		write(fd, &file_buff, 1uLL);
	}
	log_wrapper(v4, "Finished back up ", argv[1]);
	fclose(stream);
	close(fd);
	return 0;
}