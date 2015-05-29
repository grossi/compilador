#include "tree.h"
#include <stdio.h>

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

void printSpaces( int k ) {
	int i;
	for(i = 0; i < k; i++)
		printf(" ");
	return;
}

void printIndexList( NodeIndexList *node, int k ) {
	printSpaces( k );
	printf("indexList\n");
	printExp( node->exp, k+1 );
	if( node->next != NULL )
		printIndexList( node->next, k+1 );
	return;
}

void printVar( NodeVar *var, int k ) {
	printSpaces( k );
	printf("var: %s\n", var->id);
	if (var->indexList != NULL)
		printIndexList( var->indexList, k+1 );
	return;
}

void printExp( NodeExp *exp, int k ) {
	printSpaces( k );
	ExpTag etag = exp->tag;
	switch (etag)
	{
		case multiExp:
			printf("multiExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case addExp:
			printf("addExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case minusExp:
			printf("minusExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case divExp:
			printf("divExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case greaterExp:
			printf("greaterExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case lessExp:
			printf("lessExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case GEExp:
			printf("GEExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case LEExp:
			printf("LEExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case notExp:
			printf("notExp\n");
			printExp( exp->u.unary_exp, k+1 );
			return;
		case andExp:
			printf("andExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case orExp:
			printf("orExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case constantExp:
			printf("constantExp\n");
			printConstant( exp->u.k, k+1 );
			return;
		case varExp:
			printf("varExp\n");
			printVar( exp->u.var, k+1 );
			return;
		case chamadaExp:
			printf("chamadaExp\n");
			printChamada( exp->u.chamada, k+1 );
			return;
		case unMinusExp:
			printf("unMinusExp\n");
			printExp( exp->u.unary_exp, k+1 );
			return;
		case eqExp:
			printf("eqExp\n");
			printExp( exp->u.binary_exp.l, k+1 );
			printExp( exp->u.binary_exp.r, k+1 );
			return;
		case newExp:
			printf("newExp\n");
			printTipo( exp->u.newExp.tipo, k+1 );
			printExp( exp->u.newExp.exp, k+1 );
			return;
	}
}

void printListExp( NodeListaExp *listaExp, int k ) {
	printSpaces( k );
	printf("listExp\n");
	printExp( listaExp->exp, k+1 );
	printListExp( listaExp->list, k+1 );
	return;
}

void printChamada( NodeChamada *chamada, int k ) {
	printf("chamada: %s\n", chamada->id );
	printListExp( chamada->parans, k+1 );
	return;
}

void printConstant( NodeConst *constant , int k ) {
	printSpaces( k );
	ConstTag ctag = constant->tag;
	switch(ctag) {
		case vint:
			printf("constant: int %d\n", constant->u.i);
			return;
		case vchar:
			printf("constant: char %c\n", constant->u.c);
			return;
		case vstring:
			printf("constant: strin %s\n", constant->u.s);
			return;
		case vfloat:
			printf("constant: float %f\n", constant->u.f);
			return;
	}
}

void printCommand( NodeComando *command, int k ) {
	printSpaces( k );
	ComandoTag ctag = command->tag;
	switch(ctag) {
		case cif:
			printf("Command if\n");
			printExp( command->u.cif.cond, k+1 );
			printCommand( command->u.cif.command, k+1 );
			return;
		case cifelse:
			printf("Command ifelse\n");
			printExp( command->u.cifelse.cond, k+1 );
			printCommand( command->u.cifelse.ifCommand, k+1 );
			printCommand( command->u.cifelse.elseCommand, k+1 );
			return;
		case cwhile:
			printf("Command while\n");
			printExp( command->u.cwhile.cond, k+1 );
			printCommand( command->u.cwhile.command, k+1 );
			return;
		case cassign:
			printf("Command assign\n");
			printVar( command->u.cassign.var, k+1 );
			printExp( command->u.cwhile.cond, k+1 );
			return;
		case creturn:
			printf("Command return\n");
			printExp( command->u.returnExp, k+1);
			return;
		case cchamada:
			printf("Command chamada\n");
			printChamada( command->u.chamada, k+1);
			return;
		case cbloco:
			printf("Command bloco\n");
			printBloco( command->u.bloco, k+1);
			return;
	}
}

void printBloco( NodeBloco *bloco, int k ) {
	printSpaces( k );
	BlocoTag btag = bloco->tag;
	if(btag == dec) {
		printf("Bloco Dec\n");
		printDecVar( bloco->u.dec, k+1);
	} else {
		printf("Bloco Command\n");
		printCommand( bloco->u.command, k+1);
	}
	if(bloco->next != NULL)
		printBloco( bloco->next, k+1);
	return;
}

void printDecVar( NodeDecVar *decVar, int k ) {
	printSpaces( k );
	printf("Declaracao Var\n");
	printTipo( decVar->tipo, k+1 );
	printListaNomes( decVar->lista, k+1 );
	return;
}

void printListaNomes( NodeListaNomes *listaNomes, int k ) {
	printSpaces( k );
	printf("Lista de Nomes %s\n", listaNomes->id);
	if(listaNomes->next != NULL) 
		printListaNomes( listaNomes->next, k+1 );
	return;
}

void printTipo( NodeTipo *tipo, int k ) {
	int i;
	printSpaces( k );
	TipoTag ttag = tipo->tag;
	printf("tipo: ");
	switch(ttag) {
		case tint:
			printf("int");
			break;
		case tchar:
			printf("char");
			break;
		case tfloat:
			printf("float");
			break;
		case tvoid:
			printf("void");
			break;
	}
	for(i = 0; i < tipo->dimensions; i++) {
		printf("[]");
	}
	printf("\n");
	return;
}

void printParam( NodeParam *param, int k ) {
	printSpaces( k );
	printf("param: %s\n", param->id);
	printTipo( param->tipo, k+1 );
	if( param->next != NULL)
		printParam( param->next, k+1 );	
	return;
}

void printDeclista( NodeDecLista *declista, int k ) {
	printSpaces( k );
	DecTag dtag = declista->tag;
	printf("declista\n");
	if(dtag == decvar) {
		printDecVar( declista->u.var, k+1 );
	} else {
		printDecfunc( declista->u.func, k+1 );
	}
	if( declista->next!=NULL )
		printDeclista( declista->next, k+1 );
	return;
}

void printDecfunc( NodeDecFunc *decfunc, int k ) {
	printSpaces( k );
	printf("Declaracao Func id: %s\n", decfunc->id);
	printTipo( decfunc->tipo, k+1 );
	if (decfunc->params != NULL)
		printParam( decfunc->params, k+1 );
	printBloco( decfunc->bloco, k+1 );
	return;
}

void printProgram( NodeProgram *program, int k ) {
	printSpaces( k );
	printf("program\n");
	printDeclista( program->listaDec, k+1 );
	return;
}

int main()
{
	YYSTYPE startingNode;
	yyparse();
	startingNode.program = semTree;
	printProgram( startingNode.program, 0 );
	return 0;
}
