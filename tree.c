#include "tree.h"
#include <stdio.h>

void printTree( YYSTYPE node, TreeNodeTag tag, int k ) {
	int i;
	YYSTYPE nextNode;
	for(i = 0; i < k; i++)
		printf(" ");
	switch(tag)
	{
		case indexList:
			printf("indexList\n");
			nextNode.exp = node.indexList->exp;
			printTree( nextNode, Exp, k+1 );
			nextNode.indexList = node.indexList->next;
			if(nextNode.indexList != NULL)
				printTree( nextNode, indexList, k+1 );
			return;
		case var:
			printf("var: %s\n", node.var->id);
			nextNode.indexList = node.var->indexList;
			if (nextNode.indexList != NULL)
				printTree( nextNode, indexList, k+1 );
			return;
		case Exp:
		{
			ExpTag etag = node.exp->tag;
			switch (etag)
			{
				case multiExp:
					printf("multiExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
				case addExp:
					printf("addExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
				case minusExp:
					printf("minusExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
				case divExp:
					printf("divExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
				case greaterExp:
					printf("greaterExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
				case lessExp:
					printf("lessExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
				case GEExp:
					printf("GEExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
				case LEExp:
					printf("LEExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
				case notExp:
					printf("notExp\n");
					nextNode.exp = node.exp->u.unary_exp;
					printTree( nextNode, Exp, k+1 );
					return;
				case andExp:
					printf("andExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
				case orExp:
					printf("orExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
				case constantExp:
					printf("constantExp\n");
					nextNode.constant = node.exp->u.k;
					printTree( nextNode, constant, k+1 );
					return;
				case varExp:
					printf("varExp\n");
					nextNode.var = node.exp->u.var;
					printTree( nextNode, var, k+1 );
					return;
				case chamadaExp:
					printf("chamadaExp\n");
					nextNode.chamada = node.exp->u.chamada;
					printTree( nextNode, chamada, k+1 );
					return;
				case unMinusExp:
					printf("unMinusExp\n");
					nextNode.exp = node.exp->u.unary_exp;
					printTree( nextNode, Exp, k+1 );
					return;
				case eqExp:
					printf("eqExp\n");
					nextNode.exp = node.exp->u.binary_exp.l;
					printTree( nextNode, Exp, k+1 );
					nextNode.exp = node.exp->u.binary_exp.r;
					printTree( nextNode, Exp, k+1 );
					return;
			}
		}
		case listExp:
			nextNode.listExp = node.listExp->list;
			printf("listExp\n");
			printTree( nextNode, listExp, k+1 );
			return;
		case chamada:
			printf("chamada: %s\n", node.chamada->id );
			nextNode.listExp = node.chamada->parans;
			printTree( nextNode, param, k+1 );
			return;
		case constant:
		{
			ConstTag ctag = node.constant->tag;
			switch(ctag) {
				case vint:
					printf("constant: int %d\n", node.constant->u.i);
					return;
				case vchar:
					printf("constant: char %c\n", node.constant->u.c);
					return;
				case vstring:
					printf("constant: strin %s\n", node.constant->u.s);
					return;
				case vfloat:
					printf("constant: float %f\n", node.constant->u.f);
					return;
			}
		}
		case command:
		{
			ComandoTag ctag = node.command->tag;
			switch(ctag) {
				case cif:
					printf("Command if\n");
					nextNode.exp = node.command->u.cif.cond;
					printTree(nextNode, Exp, k+1 );
					nextNode.command = node.command->u.cif.command;
					printTree(nextNode, command, k+1 );
					return;
				case cifelse:
					printf("Command ifelse\n");
					nextNode.exp = node.command->u.cifelse.cond;
					printTree(nextNode, Exp, k+1 );
					nextNode.command = node.command->u.cifelse.ifCommand;
					printTree(nextNode, command, k+1 );
					nextNode.command = node.command->u.cifelse.elseCommand;
					printTree(nextNode, command, k+1 );
					return;
				case cwhile:
					printf("Command while\n");
					nextNode.exp = node.command->u.cwhile.cond;
					printTree(nextNode, Exp, k+1 );
					nextNode.command = node.command->u.cwhile.command;
					printTree(nextNode, command, k+1 );
					return;
				case cassign:
					printf("Command assign\n");
					nextNode.var = node.command->u.cassign.var;
					printTree(nextNode, var, k+1 );
					nextNode.exp = node.command->u.cwhile.cond;
					printTree(nextNode, Exp, k+1 );
					return;
				case creturn:
					printf("Command return\n");
					nextNode.exp = node.command->u.returnExp;
					printTree(nextNode, Exp, k+1);
					return;
				case cchamada:
					printf("Command chamada\n");
					nextNode.chamada = node.command->u.chamada;
					printTree(nextNode, chamada , k+1);
					return;
				case cbloco:
					printf("Command bloco\n");
					nextNode.bloco = node.command->u.bloco;
					printTree(nextNode, bloco, k+1);
					return;
			}
		}
		case bloco:
		{
			BlocoTag btag = node.bloco->tag;
			if(btag == dec) {
				printf("Bloco Dec\n");
				nextNode.decVar = node.bloco->u.dec;
				printTree(nextNode, decVar, k+1);
			} else {
				printf("Bloco Command\n");
				nextNode.command = node.bloco->u.command;
				printTree(nextNode, command, k+1);
			}
			nextNode.bloco = node.bloco->next;
			if(nextNode.bloco != NULL)
				printTree(nextNode, bloco, k+1);
			return;
		}
		case decVar:
			printf("Declaracao Var\n");
			nextNode.tipo = node.decVar->tipo;
			printTree( nextNode, tipo, k+1 );
			nextNode.listaNomes = node.decVar->lista;
			printTree( nextNode, listaNomes, k+1 );
			return;
		case listaNomes:
			printf("Lista de Nomes %s\n", node.listaNomes->id);
			nextNode.listaNomes = node.listaNomes->next;
			if(nextNode.listaNomes != NULL) 
				printTree( nextNode, listaNomes, k+1 );
			return;
		case tipo:
		{
			TipoTag ttag = node.tipo->tag;
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
			for(i = 0; i < node.tipo->dimensions; i++) {
				printf("[]");
			}
			printf("\n");
			return;
		}
		case param:
			printf("param: %s\n", node.param->id);
			nextNode.tipo = node.param->tipo;
			printTree( nextNode, tipo, k+1 );
			nextNode.param = node.param->next;
			if(nextNode.param != NULL)
				printTree( nextNode, param, k+1 );
			return;
		case declista:
		{
			DecTag dtag = node.declista->tag;
			printf("declista\n");
			if(dtag == decvar) {
				nextNode.decVar = node.declista->u.var;	
				printTree( nextNode, decVar, k+1 );
			} else {
				nextNode.decfunc = node.declista->u.func;
				printTree( nextNode, decfunc, k+1);
			}
			nextNode.declista = node.declista->next;
			if(nextNode.declista!=NULL)
				printTree( nextNode, declista, k+1 );
			return;
		}
		case decfunc:
			printf("Declaracao Func id: %s\n", node.decfunc->id);
			nextNode.tipo = node.decfunc->tipo;
			printTree( nextNode, tipo, k+1 );
			nextNode.param = node.decfunc->params;
			if (nextNode.param != NULL)
				printTree( nextNode, param, k+1 );
			nextNode.bloco = node.decfunc->bloco;
			printTree( nextNode, bloco, k+1 );
			return;
		case program:
			nextNode.declista = node.program->listaDec;
			printf("program\n");
			printTree( nextNode, declista, k+1 );
			return;
	}
}


int main()
{
	YYSTYPE startingNode;
	yyparse();
	startingNode.program = semTree;
	printTree( startingNode, program, 0);
	return 0;
}
