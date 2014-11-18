#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

void error_and_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

int main()
{
	pid_t pid;

	if ((pid = fork()) < 0) {
		error_and_die("Cannot fork new process");
	} else if (!pid) {
		printf("Child process, pid: %d\n", getpid());
		exit(0);
	} else {
		printf("Parent process, pid: %d\n", getpid());

		if (waitpid(pid, NULL, 0) < 0)
			printf("Failed to fetch child process termination status");
	}
	return 0;
}
