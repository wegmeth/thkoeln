#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define NUM_OF_CHILDS 2

void main(int argc, char *argv[]) {
	
	if(argc != 2 ) exit(-1);

	int i, id, *sharemem;
	int pid[NUM_OF_CHILDS]; 
	int footsize[2];
	
	footsize[0]=5;
	footsize[1]=3;
	int distance = (footsize[0] + footsize[1]) * 10;
	char *end;;

	id = shmget(IPC_PRIVATE, SEGSIZE, IPC_CREAT|0777);
	sharemem = (int *)shmat(id, 0, 0);
	*sharemem = distance;
	int sleepT = strtol(argv[1],NULL,10);
	for (i = 0; i < NUM_OF_CHILDS; i++) {
		pid[i] = fork();

		if (pid[i]<0) {
			perror("Fehler in Piss - Child konnte nicht angelegt werden");
			exit(1);
		}
		if (pid[i]==0) {
			while (*sharemem > 0){
				*sharemem -= footsize[i];
				usleep(sleepT);				
			}
			exit(0);
		}
	}
	for (i = 0; i < NUM_OF_CHILDS; i++)
		waitpid(pid[i], NULL, 0);


	if(*sharemem != 0 ){
		shmdt(sharemem);
		shmctl(id, IPC_RMID, 0);	
		perror("distance < 0");
		exit(1); 

	
	};
	shmdt(sharemem);
	shmctl(id, IPC_RMID, 0);	
	exit(0);	
}
