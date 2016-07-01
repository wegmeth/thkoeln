#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 8888

int com(int sd, struct socketAddrIn sIn, int *sinLen);
int stichwortSuche(FILE *sockStream, char stichword[]);

int main(){

	int sd;
	struct socketAddrIn sIn;
	int sinLen = sizeof(sIn);
	sIn.sin_family = AF_INET;
	sIn.sin_addr.s_addr = INADDR_ANY;
	sIn.sin_port = htons(SERVER_PORT);

	sd = socket(AF_INET, SOCK_STREAM,0);
	bind(sd, (struct sockaddr *)& sIn, sizeof(sIn));

	listen(sd,5);
	com(sd, sIn, &sinLen);
	unlink((const char *)& sIn);

	return EXIT_SUCCESS;
}

int com(int sd, struct socketAddrIn sIn, int *sinLen){
	int n_sd;
	char stichwort[50];


	FILE *sockstream;
	char *greez ="Hallo Stichwortsuche \n";
	char *bye ="bye\n";

	while(true){
		n_sd = accept(sd,(struct sockaddr*) &sIn, (unsigned long*)&sinLen);

		sockstream = fdopen(n_sd, "r+");
		fprintf(sockstream, "%s\n",greez);
		rewind(sockstream);
		
		while(true){
			fprintf(sockstream,"%s",&stichwort);
			rewind(sockstream);
			fscanf(sockstream, "%s", &stichwort);
			rewind(sockstream);
			if(strcmp(stichwort, "EXIT") == 0){
				break;
			}
			stichwortSuche(sockstream,stichwort);
		}
		close(n_sd);
	}
	return EXIT_SUCCESS;
}

int stichwortSuche(FILE *sockstream, char stichwort[]){

	if(strcmp("Hallo", stichwort) == 0){
		fprintf(sockstream, "%s\n","Welt");
	}else if(strcmp("Toller", stichwort) == 0){
		fprintf(sockstream, "%s\n","Tag");
	}else if(strcmp("Was", stichwort) == 0){
		fprintf(sockstream, "%s\n","geht");
	}else if(strcmp("Geh", stichwort) == 0){
		fprintf(sockstream, "%s\n","Weg");
	}else if(strcmp("Alles", stichwort) == 0){
		fprintf(sockstream, "%s\n","klar");
	}else if(strcmp("oder", stichwort) == 0){
		fprintf(sockstream, "%s\n","nicht");
	}else if(strcmp("Ping", stichwort) == 0){
		fprintf(sockstream, "%s\n","Pong");
	}

	rewind(sockstream);

	return EXIT_SUCCESS;
}















