#include "typifyTree.h"
#include <stdio.h>
#include <malloc.h>


NodeDecVar *decVar_pilha[100];
NodeDecFunc *decFunc_pilha[100];
int decVar_i;
int decFunc_i;
int escopo_pilha[100];
int escopo_i;

extern struct _NodeTipo tipoInt;
extern struct _NodeTipo tipoChar;
extern struct _NodeTipo tipoCharArray;
extern struct _NodeTipo tipoFloat;
extern struct _NodeTipo tipoVoid;


void typifyCastExpFromConditional( NodeExp **e ) {
	NodeExp *cast;
	cast = (NodeExp*) malloc(sizeof(NodeExp));
	cast->tag = castExp;	
	if( (*e)->tipo->dimensions != 0 ) {
		yyerror("condicional nao pode ser do tipo array");
	}
	if( (*e)->tipo->tag != tint ) {
		cast->tipo = &tipoInt;
		cast->u.castExp.tipo = &tipoInt;
		cast->u.castExp.exp = *e;
		*e = cast;
	}
}

void typifyCastExpFromReturn( NodeExp **e ) {
	NodeDecFunc *decFunc = decFunc_pilha[decFunc_i-1];
	NodeExp *cast;
	cast = (NodeExp*) malloc(sizeof(NodeExp));
	cast->tag = castExp;
	if( decFunc->tipo->dimensions == 0 && (*e)->tipo->dimensions == 0 ) {
		if( (*e)->tipo != decFunc->tipo ) {
			if( decFunc->tipo->tag == tint ) {
				cast->tipo = &tipoInt;
				cast->u.castExp.tipo = &tipoInt;
				cast->u.castExp.exp = *e;
				*e = cast;
			} else if( decFunc->tipo->tag == tchar ) {
				cast->tipo = &tipoChar;
				cast->u.castExp.tipo = &tipoChar;
				cast->u.castExp.exp = *e;
				*e = cast;
			} else {
				cast->tipo = &tipoFloat;
				cast->u.castExp.tipo = &tipoFloat;
				cast->u.castExp.exp = *e;
				*e = cast;
			}
		}
	} else {
		if( (*e)->tipo->dimensions != decFunc->tipo->dimensions )
			yyerror("cast de nao array para array impossivel");
		else if( (*e)->tipo->tag != decFunc->tipo->tag )
			yyerror("cast de arrays de tipos diferentes impossivel");
	}	
}

void typifyCastExpFromAssign(NodeVar *v, NodeExp **e) {
	NodeExp *cast;
	cast = (NodeExp*) malloc(sizeof(NodeExp));
	cast->tag = castExp;
	if( v->decVar->tipo->dimensions == 0 && (*e)->tipo->dimensions == 0 ) {
		if( (*e)->tipo != v->decVar->tipo ) {
			if( v->decVar->tipo->tag == tint ) {
				cast->tipo = &tipoInt;
				cast->u.castExp.tipo = &tipoInt;
				cast->u.castExp.exp = *e;
				*e = cast;
			} else if( v->decVar->tipo->tag == tchar ) {
				cast->tipo = &tipoChar;
				cast->u.castExp.tipo = &tipoChar;
				cast->u.castExp.exp = *e;
				*e = cast;
			} else {
				cast->tipo = &tipoInt;
				cast->u.castExp.tipo = &tipoChar;
				cast->u.castExp.exp = *e;
				*e = cast;
			}
		}
	} else {
		if( (*e)->tipo->dimensions != v->decVar->tipo->dimensions )
			yyerror("cast de nao array para array impossivel");
		else if( (*e)->tipo->tag != v->decVar->tipo->tag )
			yyerror("cast de arrays de tipos diferentes impossivel");
	}
}

void typifyCastExpFromBinary(NodeExp **r, NodeExp **l) {
	NodeExp *cast;
	cast = (NodeExp*) malloc(sizeof(NodeExp));
	cast->tag = castExp;

	if( (*l)->tipo->dimensions != 0 || (*r)->tipo->dimensions != 0 ) {
		yyerror("operacao nao suporta tipos array");
	}

	if( (*l)->tipo != (*r)->tipo ) {
		NodeExp *castExp = (NodeExp*) malloc(sizeof(NodeExp));
		if( (*l)->tipo->tag == tchar ) {
			if( (*r)->tipo->tag == tint ) {
				// char OP int
				cast->tipo = &tipoInt;
				cast->u.castExp.tipo = &tipoInt;
				cast->u.castExp.exp = *l;
				*l = cast;
			} else {
				// char OP float
				cast->tipo = &tipoFloat;
				cast->u.castExp.tipo = &tipoFloat;
				cast->u.castExp.exp = *l;
				*l = cast;
			}
		} else if( (*l)->tipo->tag == tint ) {
			if( (*r)->tipo->tag == tchar ) {
				// int OP char
				cast->tipo = &tipoInt;
				cast->u.castExp.tipo = &tipoInt;
				cast->u.castExp.exp = *r;
				*r = cast;
			} else {
				// int OP float
				cast->tipo = &tipoFloat;
				cast->u.castExp.tipo = &tipoFloat;
				cast->u.castExp.exp = *l;
				*l = cast;
			}
		} else {
			if( (*r)->tipo->tag == tchar ) {
				// float OP char
				cast->tipo = &tipoFloat;
				cast->u.castExp.tipo = &tipoFloat;
				cast->u.castExp.exp = *r;
				*r = cast;
			} else {
				// float OP int
				cast->tipo = &tipoFloat;
				cast->u.castExp.tipo = &tipoFloat;
				cast->u.castExp.exp = *r;
				*r = cast;
			}
		}
	}
}

void typifyIndexList( NodeIndexList *node ) {
	typifyExp( node->exp );
	if( node->next != NULL )
		typifyIndexList( node->next );
	return;
}

void typifyVar( NodeVar *var ) {
	int i;
	var->decVar = NULL;
	for(i = decVar_i-1; i >= 0; i-- ) {
		if( strcmp( var->id, decVar_pilha[i]->id ) == 0 ) {
			var->decVar = decVar_pilha[i];
			break;
		}
	}
	if(var->decVar == NULL) 
	{
		printf("var = %s\n", var->id);
		yyerror("variavel nao declarada");
	}
	if (var->indexList != NULL)
		typifyIndexList( var->indexList );
	return;
}

void typifyExp( NodeExp *exp ) {
	NodeExp *r, *l;
	ExpTag etag = exp->tag;
	r = exp->u.binary_exp.r;
	l = exp->u.binary_exp.l;
	switch (etag)
	{
		case multiExp:
			typifyExp( l );
			typifyExp( r );
			typifyCastExpFromBinary( &r, &l );
			exp->tipo = r->tipo;
			return;
		case addExp:
			typifyExp( l );
			typifyExp( r );
			typifyCastExpFromBinary( &r, &l );
			exp->tipo = r->tipo;
			return;
		case minusExp:
			typifyExp( l );
			typifyExp( r );
			typifyCastExpFromBinary( &r, &l );
			exp->tipo = r->tipo;
			return;
		case divExp:
			typifyExp( l );
			typifyExp( r );
			typifyCastExpFromBinary( &r, &l );
			exp->tipo = r->tipo;
			return;
		case greaterExp:
			typifyExp( l );
			typifyExp( r );
			exp->tipo = &tipoInt;
			return;
		case lessExp:
			typifyExp( l );
			typifyExp( r );
			exp->tipo = &tipoInt;
			return;
		case GEExp:
			typifyExp( l );
			typifyExp( r );
			exp->tipo = &tipoInt;
			return;
		case LEExp:
			typifyExp( l );
			typifyExp( r );
			exp->tipo = &tipoInt;
			return;
		case notExp:
			typifyExp( exp->u.unary_exp );
			exp->tipo = &tipoInt;
			return;
		case andExp:
			typifyExp( l );
			typifyExp( r );
			exp->tipo = &tipoInt;
			return;
		case orExp:
			typifyExp( l );
			typifyExp( r );
			exp->tipo = &tipoInt;
			return;
		case constantExp:
			typifyConstant( exp->u.k );
			exp->tipo = exp->u.k->tipo;
			return;
		case varExp:
			typifyVar( exp->u.var );
			exp->tipo = exp->u.var->decVar->tipo;
			return;
		case chamadaExp:
			typifyChamada( exp->u.chamada );
			exp->tipo = exp->u.chamada->decFunc->tipo;
			if(exp->tipo->tag == tvoid) {
				yyerror("expressao nao pode ser do tipo void");
			}
			return;
		case unMinusExp:
			typifyExp( exp->u.unary_exp );
			exp->tipo = exp->u.unary_exp->tipo;
			return;
		case eqExp:
			typifyExp( l );
			typifyExp( r );
			exp->tipo = &tipoInt;
			return;
		case newExp:
			typifyTipo( exp->u.newExp.tipo );
			typifyIndexList( exp->u.newExp.index );
			exp->tipo = (NodeTipo*) malloc(sizeof(NodeTipo));
			exp->tipo->tag = exp->u.newExp.tipo->tag;
			exp->tipo->dimensions = exp->u.newExp.index->cont;
			return;
	}
}

void typifyListExp( NodeListaExp *listaExp ) {
	typifyExp( listaExp->exp );
	if( listaExp->next != NULL)
		typifyListExp( listaExp->next );
	return;
}

void typifyChamada( NodeChamada *chamada ) {
	int i;
	chamada->decFunc = NULL;
	for(i = decFunc_i-1; i >= 0; i-- ) {
		if( strcmp( chamada->id, decFunc_pilha[i]->id ) == 0 ) {
			chamada->decFunc = decFunc_pilha[i];
			break;
		}
	}
	if(chamada->decFunc == NULL) 
	{
		printf("funcao %s\n", chamada->id);
		yyerror("funcao nao declarada");
	}
	if( chamada->parans != NULL )
		typifyListExp( chamada->parans );
	return;
}

void typifyConstant( NodeConst *constant  ) {
	ConstTag ctag = constant->tag;
	switch(ctag) {
		case vint:
			constant->tipo = &tipoInt;
			return;
		case vchar:
			constant->tipo = &tipoChar;
			return;
		case vstring:
			constant->tipo = &tipoCharArray;
			return;
		case vfloat:
			constant->tipo = &tipoFloat;
			return;
	}
}

void typifyCommand( NodeComando *command ) {
	ComandoTag ctag = command->tag;
	switch(ctag) {
		case cif:
			typifyExp( command->u.cif.cond );
			typifyCommand( command->u.cif.command );
			typifyCastExpFromConditional( &(command->u.cif.cond) );
			return;
		case cifelse:
			typifyExp( command->u.cifelse.cond );
			typifyCommand( command->u.cifelse.ifCommand );
			typifyCommand( command->u.cifelse.elseCommand );
			typifyCastExpFromConditional( &(command->u.cifelse.cond) );
			return;
		case cwhile:
			typifyExp( command->u.cwhile.cond );
			typifyCommand( command->u.cwhile.command );
			return;
		case cassign:
			typifyVar( command->u.cassign.var );
			typifyExp( command->u.cassign.exp );
			typifyCastExpFromAssign( command->u.cassign.var, &(command->u.cassign.exp) );
			return;
		case creturn:
			typifyExp( command->u.returnExp );
			typifyCastExpFromReturn( &(command->u.returnExp) );
			return;
		case cchamada:
			typifyChamada( command->u.chamada );
			return;
		case cbloco:
			escopo_pilha[escopo_i] = decVar_i;
			escopo_i++;
			typifyBloco( command->u.bloco);
			escopo_i--;
			decVar_i = escopo_pilha[escopo_i];
			return;
	}
}

void typifyBloco( NodeBloco *bloco ) {
	BlocoTag btag = bloco->tag;
	if(btag == dec) {
		typifyDecVar( bloco->u.dec);
	} else {
		typifyCommand( bloco->u.command);
	}
	if(bloco->next != NULL)
		typifyBloco( bloco->next);
	return;
}

void typifyDecVar( NodeDecVar *decVar ) {
	decVar_pilha[decVar_i] = decVar;
	decVar_i++;
	typifyTipo( decVar->tipo );
	if( decVar->next != NULL ) {
		typifyDecVar( decVar->next );
	}
	return;
}

void typifyListaNomes( NodeListaNomes *listaNomes ) {
	if(listaNomes->next != NULL) 
		typifyListaNomes( listaNomes->next );
	return;
}

void typifyTipo( NodeTipo *tipo ) {
	int i;
	TipoTag ttag = tipo->tag;
	switch(ttag) {
		case tint:
			break;
		case tchar:
			break;
		case tfloat:
			break;
		case tvoid:
			break;
	}
	for(i = 0; i < tipo->dimensions; i++) {
	}
	return;
}

void typifyParam( NodeParam *param ) {
	NodeDecVar *decVar;
	decVar = (NodeDecVar*) malloc(sizeof(NodeDecVar));
	decVar->tipo = param->tipo;
	decVar->id = param->id; 
	decVar->next = NULL;
	param->decVar = decVar;
	typifyDecVar( decVar );
	typifyTipo( param->tipo );
	if( param->next != NULL)
		typifyParam( param->next );	
	return;
}

void typifyDeclista( NodeDecLista *declista ) {
	DecTag dtag = declista->tag;
	if(dtag == decvar) {
		typifyDecVar( declista->u.var );
	} else {
		typifyDecfunc( declista->u.func );
	}
	if( declista->next!=NULL )
		typifyDeclista( declista->next );
	return;
}

void typifyDecfunc( NodeDecFunc *decfunc ) {
	escopo_pilha[escopo_i] = decVar_i;
	escopo_i++;
	decFunc_pilha[decFunc_i] = decfunc;
	decFunc_i++;
	typifyTipo( decfunc->tipo );
	if (decfunc->params != NULL) {
		typifyParam( decfunc->params );
	}
	typifyBloco( decfunc->bloco );
	escopo_i--;	
	decVar_i = escopo_pilha[escopo_i];
	return;
}

void typifyProgram( NodeProgram *program ) {
	int decVar_i = 0;
	int decFunc_i = 0;
	int escopo_i = 0;
	typifyDeclista( program->listaDec );
	return;
}
