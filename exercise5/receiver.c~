#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h> 
#include <errno.h>

struct text_message {
	long type;
	char text[100];
};

void main(int argc, char *argv[]) {
	int msid, v;
	struct msqid_ds buf;
	struct text_message message;

	if (argc !=2) {
		printf("msqreceive: msgrcv <key>\n");
		exit(1);
	}

	int key = atoi(argv[1]);
	msid = msgget(key, 0);

	if (msid == -1){
		printf("cannot get message queue\n");
		exit(1);
	}
	while(1){	
		printf("Bitte Nachrichtentyp wählen:\n\t0 Beenden\n\t1 sehr wichtig\n\t2 wichtig\n\t3 normal\n");

	
		int sType=0;	
		scanf("%i",&sType);
	
		int startRange=0;
		int endRange =0;

		if(sType==0) exit(0);
		else if(sType == 1){startRange = 1;  endRange =5;}
		else if(sType == 2){startRange = 6; endRange = 9;}
		else if(sType == 3){startRange = 10; endRange = 20;}

		int i = startRange;
		for(i= startRange; i<=endRange;i++){
			while(1){
				v = msgrcv(msid, &message, 100, i , IPC_NOWAIT);
				if ((v<0)) break;
				else printf("Typ:%ld - Nachricht:%s\n",message.type, message.text);
			}
		}

		if(msgctl(msid,IPC_STAT, &buf) == -1 ){
			printf("msgctl");
		}

		int num = buf.msg_qnum;
		printf("Queue laenge:%i\n",num);
		if(num == 0 ){
			msgctl(msid,IPC_RMID, NULL);
			exit(1);
		}
	}
}
