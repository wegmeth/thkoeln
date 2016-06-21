#include <stdio.h>
#include <string.h> 
#include <time.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h> 
#include <sys/stat.h> 

char* formatRights(int st_mode)
{
	int i;
	char* l_rwx = (char*)malloc(sizeof(char)*10);
	if(l_rwx == NULL){
		return (char*)NULL;
	}
	const char rwx[] = "rwxrwxrwx";

	int bits[] = {
		S_IRUSR,S_IWUSR,S_IXUSR,
		S_IRGRP,S_IWGRP,S_IXGRP,
		S_IROTH,S_IWOTH,S_IXOTH
	};

	for(i = 0; i < 9; i++) {
		if(st_mode & bits[i])
			l_rwx[i]=rwx[i];
		else
			l_rwx[i] = '-';
	}
	l_rwx[9]='\0';
	return l_rwx;
}

void main(int argc, char *argv[]) {
	if(argc < 2 ) exit(1);
	
	struct stat attr;	

	int i;
	for(i = 1; i<argc;i++){
		stat(argv[i], &attr);
		printf("Datei\t\t\t: %s\n",argv[i]);
		printf("Dateigroesse\t\t: %ld Bytes\n",attr.st_size);
		printf("Besitzer\t\t: %i\n",attr.st_uid);
		printf("Inode Nummer\t\t: %ld\n",attr.st_ino);
		printf("letzter Zugriff\t\t: %s",ctime(&(attr.st_atime)));
		printf("letzte Aenderung\t: %s",ctime(&(attr.st_mtime)));
		printf("letzte Inode Aenderung\t: %s",ctime(&(attr.st_ctime)));
		printf("Zugriffsrechte\t\t: %s\n",formatRights(attr.st_mode));
		printf("\n");
	}
	exit(0);
}
