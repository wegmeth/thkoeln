#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printEnv(char *arr[]){
	while (*arr != 0){
		printf("%s\n",*arr++);
	}
	printf("------------\n");
}

int main(int argc, char *argv[], char *envp[]) {
	printEnv(envp);
	
	setenv("BSPRAKTIKUM","ISTSUPER",0);	

	char line[500];
	printf("Eingabe:\n");
	scanf("%s", line);
	printf("%s : %s\n",line, getenv(line));

	return 0;
}

