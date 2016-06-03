#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 255
void rot13(char a[], char b[]){
        int i = 0, lo = 65, hi = 90, diff = 32, rot = 13;
        while(a[i] != '\0'){
                /*uppercase*/
                if(a[i] > lo-1 && a[i] < hi+1){
                        if(a[i]-lo < rot)
                                b[i] = a[i] + rot;
                        else
                                b[i] = a[i] - rot;
                }
                /*lowercase*/
                else if (a[i] > lo+diff-1 && a[i] < hi+diff+1){
                        if(a[i]-(lo+diff) < rot )
                                b[i] = a[i] + rot;
                        else
                                b[i] = a[i] - rot;
                }
                /*no alpha*/
                else
                        b[i] = a[i];
                i++;
        }
        b[i] = '\0';
return;
}

int main(int argc, char *argv[]){
	int status = mkfifo("FIFO_1",0777);
	FILE *fp;
	char output[MAX];
	
	if(argc != 2 ){
		perror("FALSCHE AUFRUF");
		exit(2);
	}else if(status == -1){
		unlink("FIFO_1");
		printf("FEHER PIPE ERSTELLUNG");
	}else{
		if((fp=fopen("FIFO_1","w")) == 0){
			perror("fopen()");
			unlink("FIFO_1");
			exit(1);
		}else{
			rot13(argv[1],output);
			fprintf(stderr,"%s\n",output);
			fprintf(fp,"%s\n",output);
		}
	}
	fclose(fp);
	return 0;
}
