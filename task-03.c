#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    mqd_t mq;               // message queue
    struct mq_attr ma;      // message queue attributes
    int status = 0;
    int a = 5;
    int b = 0;
    char *c="str";
	char *buffer;
	struct mq_attr attr;
    printf("a = %d, b = %d\n", a, b);

    // Specify message queue attributes.
    ma.mq_flags = 0;                // blocking read/write
    ma.mq_maxmsg = 60;              // maximum number of messages allowed in que                                                                                        ue
    ma.mq_msgsize = 120;    // messages are contents of an int
    ma.mq_curmsgs = 0;              // number of messages currently in queue

    // Create the message queue with some default settings.
    mq = mq_open("/test_queue", O_RDWR | O_CREAT|O_EXCL, 0700, &ma);
    int x = fork();
    // -1 indicates an error.
    if (mq == -1)
    {
        printf("Failed to create queue.\n");
        status = 1;
    }

    if (x==0 && status == 0)
    {
	mq_unlink("/test_queue");
	mq = mq_open("/test_queue", O_RDWR | O_CREAT|O_EXCL, 0700, &ma);
        char *sendmsg = "Hello World";
        printf("child code \n");
        //a++;
	size_t s1 = strlen(sendmsg);
       printf("-----%d\n",s1);
// mq.mq_msgsize = s1;
 status = mq_send(mq, (char *)sendmsg, s1, 1);
        printf("child finished%d\n",status);
    }

    if (x>0 && status == 0)
    {
        printf("sdfs");
        // buffer = malloc(attr.mq_msgsize);
		//if (buffer == NULL)
		//errExit("malloc");
	char rec[11];
        printf("parent code");
        status = mq_receive(mq, (char *) &rec,11, NULL);

        sleep(3);
    if ((status == 0) && (mq_close(mq) == -1))
    {
        printf("Error closing message queue.\n");
        status = 1;
    }

    if ((status == 0) && (mq_unlink("test_queue") == -1))
    {
        printf("Error deleting message queue.\n");
        status = 1;
    }

    printf("a = %d, b = %d, c=%s\n", a, b,rec);
}
    return status;
}

