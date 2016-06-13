#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#define NUM_OF_CHILDS 300

int main(int argc, char *argv[]) {
	int pid[NUM_OF_CHILDS]; 
	int i;
	for (i = 0; i < NUM_OF_CHILDS; i++) {
		pid[i] = fork();	
		if (pid[i]==0){
			return execlp("cPiss","cPiss",i, NULL);
		}else if(pid[i]<0){
			perror("Kind konnte nicht erzeugt werden\n");
			exit(1);
		}
	}

	int ret[NUM_OF_CHILDS];
	for (i = 0; i < NUM_OF_CHILDS; i= i + 10){
		waitpid(pid[i], &ret[i], 0);
	}

	for (i = 0; i < NUM_OF_CHILDS; i++){
		printf("%i - %i\n", WEXITSTATUS(ret[i]), i);
		 
	
	}	
	exit(0);	
}
