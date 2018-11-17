%code top{
#include <stdio.h>
#include "scanner.h"
#include "semantic.h"
#include "symbols.h"
}

%code provides{
void yyerror(const char *);
extern int yylexerrs;
extern int yynerrs;
}

%defines "parser.h"
%output "parser.c"
%define api.value.type {char *}
%define parse.error verbose
%token FDT IDENTIFICADOR CONSTANTE PROGRAMA VARIABLES DEFINIR LEER ESCRIBIR CODIGO FIN
%token ASIGNACION "<-"
//tabla precedencias

%right ASIGNACION
%left '+' '-'
%left '/' '*'
%precedence NEG

%% 
todo			: {comenzar();}programa { if (yynerrs || yylexerrs) YYABORT; else YYACCEPT;}
			;
programa             	: PROGRAMA VARIABLES variable CODIGO codigo FIN {terminar();}
                     	;

variable             	: variable DEFINIR IDENTIFICADOR '.' {if (buscarEnDiccionario($3)!=1){declarar($3);}else {errorIdRepetido($3);YYERROR;};}
			| %empty 
			| error '.'
                     	;

codigo               	: codigo sentencia '.' 
			| sentencia '.' 
			| error '.'
                     	;
	
sentencia            	: LEER '('listaIdentificadores')' 
                     	| ESCRIBIR '('listaExpresiones')' 
                     	| identificador ASIGNACION expresion {asignar($3,$1);}
                     	;

identificador		: IDENTIFICADOR {if (buscarEnDiccionario($1)!=1){ erorrIdNoDeclarado($1);YYERROR;}; $$=$1;}
			;

listaIdentificadores 	: identificador {leer($1);}
                     	|  listaIdentificadores ',' identificador {leer($2);}
                    	;

listaExpresiones     	: expresion {escribir($1);}
                     	| listaExpresiones ','  expresion 
                    	;

expresion            	: expresion '+' expresion {$$=operar('+',$1,$3);}
                     	| expresion '-' expresion {$$=operar('-',$1,$3);}
			| expresion '*' expresion {$$=operar('*',$1,$3);}
                     	| expresion '/' expresion {$$=operar('/',$1,$3);}
			| identificador 
			| CONSTANTE
                        | '-' expresion %prec NEG {$$=invertir($2);}
			| '('expresion')' {$$=$2;}
			;

%%

void yyerror(const char* s){
	printf("Línea: %d\t%s\n", yylineno, s);
}

