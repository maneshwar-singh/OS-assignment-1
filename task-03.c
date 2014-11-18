#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mqueue.h>
#include <unistd.h>

void error_and_die(const char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}


int main (void) {
	        int retVal;
        	mqd_t msg_queue;
		struct mq_attr mqAttr;

		retVal = mq_unlink ("/messagequeue");

		mqAttr.mq_maxmsg = 10;
		mqAttr.mq_msgsize = 1024;
		msg_queue = mq_open ("/messagequeue", O_RDWR|O_CREAT, S_IWUSR|S_IRUSR, &mqAttr);
		if (msg_queue < 0) 
			error_and_die("Message Queue Creation Failed!\n");
		
		//Child process creation.
        	pid_t pid=fork();
		if(pid==0){
			mqd_t childmq;			
			childmq = mq_open ("/messagequeue", O_RDWR);
			if (childmq < 0) 
				error_and_die("MessageQueue opening failed in Child");
			retVal = mq_send (childmq, "Hello World!", sizeof ("Hello World!"), 1);
			 printf ("Sent Message in child: Hello World!.\n" );
			if (retVal < 0) 
				error_and_die("Message sending failed in Child");

			mq_close (childmq);
		}
		else{
			if (waitpid(pid, NULL, 0) < 0)
                        	printf("Failed to fetch child process termination status");
			struct mq_attr mqAttr;
			char *receivedmessage;
			mq_getattr(msg_queue, &mqAttr);
			receivedmessage =(char *) malloc(mqAttr.mq_msgsize );
			retVal = mq_receive (msg_queue, receivedmessage, mqAttr.mq_msgsize, NULL);
			if (retVal < 0) 
				error_and_die("Message sending failed in Child");

			printf ("Received Message in parent: %s.\n", receivedmessage);

			mq_close (msg_queue);
		}
    		return 0;
}

