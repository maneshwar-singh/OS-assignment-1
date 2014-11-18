#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mqueue.h>

#define MQNAME "/pax"
#define MQMESG "Hello there!"

int main (void) {
	int rc;
	mqd_t svrHndl;
    struct mq_attr mqAttr;

    printf ("Bringing up server.\n");
    rc = mq_unlink (MQNAME);
    if (rc < 0) {
        printf ("   Warning %d (%s) on server mq_unlink.\n",
            errno, strerror (errno));
    }

    mqAttr.mq_maxmsg = 10;
    mqAttr.mq_msgsize = 1024;
    svrHndl = mq_open (MQNAME, O_RDWR|O_CREAT, S_IWUSR|S_IRUSR, &mqAttr);
    if (svrHndl < 0) {
        printf ("   Error %d (%s) on server mq_open.\n",
            errno, strerror (errno));
        exit (1);
    }
    printf ("   Server opened mqd_t of %d.\n", svrHndl);

	int pid=fork();
if(pid==0){
mqd_t cliHndl;
    printf ("Client sending.\n");
    cliHndl = mq_open (MQNAME, O_RDWR);
    if (cliHndl < 0) {
        printf ("   Error %d (%s) on client mq_open.\n",
            errno, strerror (errno));
        exit (1);
    }
    printf ("   Client opened mqd_t of %d.\n", cliHndl);

    rc = mq_send (cliHndl, MQMESG, sizeof (MQMESG), 1);
    if (rc < 0) {
        printf ("   Error %d (%s) on client mq_send.\n",
            errno, strerror (errno));
        exit (1);
    }

    mq_close (cliHndl);
}
else{
    char buffer[2048];
    printf ("Server receiving on mqd_t %d.\n", svrHndl);
    rc = mq_receive (svrHndl, buffer, sizeof (buffer), NULL);
    if (rc < 0) {
        printf ("   Error %d (%s) on server mq_receive.\n",
            errno, strerror (errno));
        exit (1);
    }
    printf ("   Received [%s].\n", buffer);
    
mq_close (svrHndl);
}
    return 0;
}
