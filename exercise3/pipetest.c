#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


typedef struct COMMANDS{
	char com[10];
	char opt[2][10];
	}Command;

int main(int argc, char *argv[], char *envp[]) {
	int i;
	Command commands[2];
	int comC=-1;	

	for(i=1;i<argc; i++){
		if(argv[i][0] == '-'){
			strcpy(commands[comC].opt[1],argv[i]);
		}else{
			strcpy(commands[++comC].com,argv[i]);
			strcpy(commands[comC].opt[0],argv[i]);
		} 
	}

	int pid[2];
	int pipe_connect[2];
	pipe(pipe_connect);
	
	pid[0] = fork();
	pid[1] = fork();

	if(pid[0] < 0 || pid[1] < 0 ){
		printf("Fehler bei der Erzeugung der Prozesse");
		exit(1);
	}	
	
	if(pid[0]==0){
		dup2(pipe_connect[1],1);
		close(pipe_connect[0]);
		execvp(commands[0].com,commands[0].opt);
	}else if(pid[1]==0){
		dup2(pipe_connect[0], 0);
		close(pipe_connect[1]);
		execvp(commands[1].com,commands[1].opt);
	}else{
		close(pipe_connect[0]);
		close(pipe_connect[1]);
		waitpid(pid[0],NULL,0);
		waitpid(pid[1],NULL,0);
	}

	return 0;
}
