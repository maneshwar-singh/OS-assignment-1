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
    int child_exitstatus=0;
    
    if(child < 0){
	error_and_die("Cannot Fork The Child");
	_exit(-1);	
    }
    if(pipe < 0){
	error_and_die("Error Creating Pipe");
    }	
    if(child==0)
    {	        
        close(filedes[0]);
        write(filedes[1],"hahahaha", 9);        
        _exit(1);
    }
    else if(child>0)
    {
        char message[9];
        wait(&child_exitstatus);        
        close(filedes[1]);
        read(filedes[0],message,9);
        printf("Message from child is :%s\n", message);
    }
    return 0;
}


