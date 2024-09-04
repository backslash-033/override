int main(void) {
	long	ptrace_return;
	int		wait_status;
	char	buff [128];
	int		pid;
	
	pid = fork();
	bzero(buff, 128);
	wait_status = 0;
	if (pid == 0) {
		prctl(1, 1);
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		puts("Give me some shellcode,  k");
		gets(buff);
	}
	else {
		do {
			wait(&wait_status);
			if (((wait_status & 0x7f) == 0) ||
				('\0' < (char)((wait_status & 0x7f) + 1) >> 1)) {
				puts("child is exiting...");
				return 0;
			}
			ptrace_return = ptrace(PTRACE_PEEKUSER, pid, 0x2c, 0);
		} while (ptrace_return != 0xb);
		puts("no exec() for you");
		kill(pid, 9);
	}
	return 0;
}