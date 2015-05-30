#ifndef PRINT_TREE_H
#define PRINT_TREE_H
#include "tree.h"

/*
	Estrutura da arvore no .h : 
	typedef struct _NodeIndexList NodeIndexList;
	typedef struct _NodeVar NodeVar;
	typedef struct _NodeExp NodeExp;
	typedef struct _NodeListaExp NodeListaExp;
	typedef struct _NodeChamada NodeChamada;
	typedef struct _NodeConst NodeConst;
	typedef struct _NodeComando NodeComando;
	typedef struct _NodeBloco NodeBloco;
	typedef struct _NodeDecVar NodeDecVar;
	typedef struct _NodeListaNomes NodeListaNomes;
	typedef struct _NodeTipo NodeTipo;
	typedef struct _NodeParam NodeParam;
	typedef struct _NodeDecLista NodeDecLista;
	typedef struct _NodeDecFunc NodeDecFunc;
	typedef struct _NodeProgram NodeProgram;
*/

void printConstant( NodeConst *constant , int k );
void printDecfunc( NodeDecFunc *decfunc, int k );
void printExp( NodeExp *exp, int k );
void printChamada( NodeChamada *chamada, int k );
void printTipo( NodeTipo *tipo, int k );
void printDecVar( NodeDecVar *decVar, int k );
void printCommand( NodeComando *command, int k );
void printVar( NodeVar *var, int k );
void printProgram( NodeProgram *program, int k );
void printListExp( NodeListaExp *listaExp, int k );
void printIndexList( NodeIndexList *node, int k );
void printParam( NodeParam *param, int k );
void printDeclista( NodeDecLista *declista, int k );
void printListaNomes( NodeListaNomes *listaNomes, int k );
void printBloco( NodeBloco *bloco, int k );

#endif
