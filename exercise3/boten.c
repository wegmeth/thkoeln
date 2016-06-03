#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 255

int main(void){
	FILE *fp;
	char str[MAX];

	if((fp = fopen("FIFO_1","r"))==NULL){
		perror("fopen()");
		exit(0);
	}else{
		fgets(str, MAX, fp);
		printf("%s\n",str);
		fclose(fp);
		exit(0);
	}

	return 0;
}

