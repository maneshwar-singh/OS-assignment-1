#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	pid_t pid;

	if ((pid = fork()) < 0) {
		printf("Cannot fork new process");
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
