#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define CHILD 2

int main(){
	int i, shm_id, sem_id, *shar_mem, pid[CHILD], distance;
	unsigned short marker[1];
	
	int foots[CHILD];
	foots[0] = 5 ;
	foots[1] = 2;

	distance = (5 + 2 ) * 20;

	sem_id = semget (IPC_PRIVATE, 1, IPC_CREAT|0644);

	if(sem_id == -1){
		perror("Die Gruppe konnte nicht angelegt werden");
		exit(1);
	}

	marker[0] = 1;
	semctl(sem_id, 1, SETALL, marker);
	shm_id= shmget(IPC_PRIVATE, SEGSIZE, IPC_CREAT|0644);

	if(shm_id == -1){
		perror("Seg error");
		exit(1);
	}

	shar_mem = (int *)shmat(shm_id,0,0);
	*shar_mem =distance;

	for(i=0;i<2;i++){
		pid[i]=fork();
		
		if(pid[i]==-1){
			perror("Kind wurde nicht erstellt");
			exit(1);
		}
		if(pid[i]==0){
			struct sembuf enter, leave;
			enter.sem_num = leave.sem_num =0;
			enter.sem_flg = leave.sem_flg=SEM_UNDO;

			enter.sem_op = -1;
			leave.sem_op=1;

			while(1){
			
				semop(sem_id, &enter, 1);
				if(*shar_mem>0){	
					*shar_mem-=foots[i];
					semop(sem_id, &leave, 1);
					printf("kind:%i\n", i);
				}else{
					semop(sem_id, &leave,1);
					break;
				}
			
			semop(sem_id, &leave, 1);
			}
			exit(0);
		}
	}
	for(i=0;i>CHILD;i++)
		waitpid(pid[i],NULL,0);
	

	printf("%i",*shar_mem);

	shmdt(shar_mem);
	shmctl(shm_id, 0, IPC_RMID);
	semctl(sem_id, 0, IPC_RMID);

	return 0;
}
