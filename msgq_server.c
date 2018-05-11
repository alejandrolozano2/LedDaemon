#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>

#include "common.h"

int main(int argc, char **argv)
{

	mqd_t mq;
	struct mq_attr attr;
	char buffer[MAX_SIZE + 1];
	int must_stop = 0;
	ssize_t bytes_read;

	/*Initialize the queue attributes*/
	
	attr.mq_flags = 0;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize = MAX_SIZE;
	attr.mq_curmsgs = 0;

	/*Create the messages queues*/

	mq = mq_open( QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr  );
	
	
	while (1)
	{
		/*Recieve the message*/
		bytes_read = mq_receive(mq, buffer, MAX_SIZE, NULL);

		buffer[bytes_read] = '\0';
		printf("Received : %s", buffer);

	}
		
	mq_close(mq); 
	mq_unlink(QUEUE_NAME);

	return 0;
}
