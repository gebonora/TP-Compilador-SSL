#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"
#include "parser.h"
#include "scanner.h"
#include "semantic.h"


int contadorTemporal = 1;

void generar(char*operador,char*a,char*b,char*c){
	printf("%s %s, %s %s \n", operador,a,b,c);
}

void comenzar(){
	generar("Load","rtlib","","");
}

void terminar(){
	puts("Stop,");
}

void asignar(char*a,char*b){
	generar("Store",a,b,"");
}

void declarar(char*a){
	colocarId(a);
	generar("Declare",a,"Integer","");
}

char* crearTemporal(){
	char* variableTemporal = malloc(15);
	sprintf(variableTemporal,"Temp#%d", contadorTemporal);
	contadorTemporal++;
	declarar(variableTemporal);
	return variableTemporal;
}	
	
void leer(char*a){
	generar("Read",a,"Integer","");
}

void escribir(char*a){
	generar("Write",a,"Integer","");
}

char* operar(char op,char*a,char*b){
	char* temporal = crearTemporal();
	char* bufferOp = malloc(5);
	
	switch(op) {
	case '+':
		strcpy(bufferOp, "ADD");
	break;
	case '-':
		strcpy(bufferOp, "SUBS");
	break;
	
	case '/':
		strcpy(bufferOp, "DIV");
	break;
	
	case '*':
		strcpy(bufferOp, "MULT");
	break;
	}
	printf("%s %s, %s, %s\n",bufferOp,a,b,temporal);
	return temporal;
}

char* invertir(char*a){
	char* temporal = crearTemporal();
	printf("Inv %s, , %s\n",a,temporal);
	return temporal;
}


void errorIdRepetido(char*a){
	printf("Línea #%d: Error semántico: identificador %s ya declarado\n",yylineno,a);
	nErroresSemanticos++;
}

void erorrIdNoDeclarado(char*a){
	printf("Línea #%d: Error semántico: identificador %s no fue declarado\n",yylineno,a);
	nErroresSemanticos++;
}	
	

