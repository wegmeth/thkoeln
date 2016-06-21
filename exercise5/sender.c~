#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h> 

struct text_message {
	long type;
	char text[100];
};

void main(int argc, char *argv[]) {
	int msid, v;
	struct text_message message; 
	
	if (argc != 4) {
		printf("usage: msqsend <key> <type> <text>\n");
		exit(1);
	}

	int key =atoi(argv[1]);
	msid = msgget(key, IPC_CREAT|0666);
	
	if (msid == -1) {
		perror("cannot get or create message queue\n");
		exit(1);
	}
	
	message.type = atoi(argv[2]);
	strcpy(message.text, argv[3]);
	
	/* Write message onto the queue */
	v = msgsnd(msid, &message, strlen(argv[3])+1, 0);
	
if (v<0)
		printf("error writing to queue\n");
}

