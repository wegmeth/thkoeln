#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	int i;
	int ret=0;
   char operation ='+';
	
	int val;
	char *end;	
	if(argc<2){
		printf("nix da\n");
		return 1;
	}	

	val = strtol(argv[1],&end,10);
	if(*end!=0){
		printf("Eingabe muss mit Zahl beginnen\n");
		return 1;
	}
	for(i=1;i<argc;i++){		
		val = strtol(argv[i],&end,10);		
   	//wenn die operation gesetzt ist, wird jetzt eine zahl verlang!
      if(operation!='\0'){
					 //dann können wir auch rechnen, nur was,...
          switch(operation){
                        	case '+': ret = ret + val; break;
                                case '-': ret = ret - val; break;
                                case 'x': ret = ret * val; break;
                                case '/': ret = ret / val; break;
				default: printf("ungueltige eingabe, erwarte Operant - %c\n",operation); return 1;
                      	 }
			operation='\0';
                }else{
                //unsere Operation ist nicht gesetzt, also erwarten wir eine 
                        operation =argv[i][0];		
                }
        }
	printf("%i\n",ret);
        return 0;
}

