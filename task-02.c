#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
int main()
{
    pid_t child;
    int filedes[2];
    pipe(filedes);
    child= fork();
    int child_exitstatus=0;
    
    if(child < 0){
	printf("Cannot Fork The Child");
	_exit(-1);	
    }
    if(pipe < 0){
	printf("Error Creating Pipe");
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


