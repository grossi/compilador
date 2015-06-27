#ifndef TIPIFY_TREE_H
#define TIPIFY_TREE_H
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


void typifyIndexList( NodeIndexList *node );
void typifyVar( NodeVar *var );
void typifyExp( NodeExp *exp );
void typifyListExp( NodeListaExp *listaExp );
void typifyChamada( NodeChamada *chamada );
void typifyConstant( NodeConst *constant  );
void typifyCommand( NodeComando *command );
void typifyBloco( NodeBloco *bloco );
void typifyDecVar( NodeDecVar *decVar );
void typifyListaNomes( NodeListaNomes *listaNomes );
void typifyTipo( NodeTipo *tipo );
void typifyParam( NodeParam *param );
void typifyDeclista( NodeDecLista *declista );
void typifyDecfunc( NodeDecFunc *decfunc );
void typifyProgram( NodeProgram *program );

#endif
