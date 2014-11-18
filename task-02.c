#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void error_and_die(const char *msg) {
	perror(msg);
  	exit(EXIT_FAILURE);
}

int main()
{
    	pid_t child;
    	int filedes[2];
    	pipe(filedes);
    	child= fork();
    
    	if(child < 0)
		error_and_die("Cannot Fork The Child");
    	if(pipe < 0)
		error_and_die("Error Creating Pipe");
    
    	if(child==0)
    	{	        
        	close(filedes[0]);
        	write(filedes[1],"Hello World!",11);
		_exit(1);        
    	}
    	else if(child>0)
    	{
        	char message[12];
		if (waitpid(child, NULL, 0) < 0)
                        printf("Failed to fetch child process termination status");
        
		close(filedes[1]);
        	read(filedes[0],message,12);
        	printf("Message from child is :%s\n", message);
    	}
    	return 0;
}


