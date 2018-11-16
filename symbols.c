#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "scanner.h"
#include "semantic.h"
#include "symbols.h"

char **diccionario;

int tamanioDiccionario = 0;

int buscarEnDiccionario(char* a){
	int flag=0;
	for (int i=0;i<tamanioDiccionario;i++){
		if (strcmp(diccionario[i],a)==0){
			flag = 1;
			break;
		}
	}return flag; //0 si no esta, 1 si esta 
}

void colocarId(char* a){
	char **backup = realloc(diccionario, (tamanioDiccionario+ 1) * sizeof a);
	if(backup != NULL) {
		backup[tamanioDiccionario] = (char *) malloc(sizeof a);
		sprintf(backup[tamanioDiccionario], a, sizeof a);
		tamanioDiccionario++;
		diccionario = backup;
		
	}
}

void inicializar(){
	colocarId("leer");
	colocarId("fin");
	colocarId("codigo");
	colocarId("variables");
}

