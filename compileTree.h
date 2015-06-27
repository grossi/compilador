#ifndef COMPILE_TREE_H
#define COMPILE_TREE_H
#include "tree.h"


void compileIndexList( NodeIndexList *node );
void compileExp( NodeExp *exp );
void compileListExp( NodeListaExp *listaExp );
void compileChamada( NodeChamada *chamada );
void compileConstant( NodeConst *constant  );
void compileCommand( NodeComando *command );
void compileBloco( NodeBloco *bloco );
void compileDecVar( NodeDecVar *decVar );
void compileListaNomes( NodeListaNomes *listaNomes );
void compileTipo( NodeTipo *tipo );
void compileParam( NodeParam *param, int offset );
void compileDeclista( NodeDecLista *declista );
void compileDecfunc( NodeDecFunc *decfunc );
void compileProgram( NodeProgram *program );
void jumpFalse( NodeExp *exp, int label );
void jumpTrue( NodeExp *exp, int label );
void printLabel( int l );
void printJump( int l );
void printCompare( NodeExp *exp );
void compileComparativeExp( NodeExp *exp );
void compileAlgebricExp( NodeExp *exp, char *op );

#endif
