#ifndef SEMANTIC_H_INCLUDED
#define SEMANTIC_H_INCLUDED
extern int nErroresSemanticos;
void generar(char*operador,char*a,char*b,char*c);
void comenzar();
void terminar();
void asignar(char*a,char*b);
void declarar(char*a);
char* crearTemporal();
void leer(char*a);
void escribir(char*a);
char* operar(char op,char*a,char*b);
char* invertir(char*a);
void errorIdRepetido(char*a);
void erorrIdNoDeclarado(char*a);
#endif
