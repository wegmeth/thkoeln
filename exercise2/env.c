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
	
	char value[100];
	strcpy(value,getenv(line));
	
	if(value[0]=='\0'){
		printf("var nicht gefunden \n");
		return 0;
	}
	printf("%s : %s\n",line,value);

	return 0;
}

