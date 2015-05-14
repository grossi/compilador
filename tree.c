#include "tree.h"

typedef union YYSTYPE YYSTYPE;

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
			printTree( nextNode, exp, k+1 );
			nextNode.indexList = node.indexList->next;
			if(nextNode!= NULL)
				printTree( nextNode, indexList, k+1 );
			return;
		case var:
			printf("var: %s\n" node.var->id);
			nextNode.indexList = node.var->indexList;
			if (index.list != NULL)
				printTree( nextNode, indexList, k+1 );
			return;
		case exp:      
			return;
		case listExp:
			nextNode.node = node.listExp->
			printf("listExp\n");
			printTree( nextNode, listExp, k+1 );
			return;
		case chamada:
			printf("chamada: %s\n". node.chamada->id );
			nextNode.parans = node.chamada->parans;
			printTree( nextNode, parans, k+1 );
			return;
		case constant:
			ConstTag tag = node.constant->tag;
			switch(tag) {
				case vint:
					printf("constant: int %d", node.constant->u.i)
					return;
				case vchar:
					printf("constant: char %c", node.constant->u.c)
					return;
				case vstring:
					printf("constant: strin %s", node.constant->u.s)
					return;
				case vfloat:
					printf("constant: float %f", node.constant->u.f)
					return;
			}
		case command:
			ComandoTag tag = node.command->tag;
			switch(tag) {
				case cif:
					printf("Command if\n");
					nextNode.exp = node.command->u.cif.cond;
					printTree(nextNode, exp, k+1 );
					nextNode.command = node.command->u.cif.command;
					printTree(nextNode, command, k+1 );
					return;
				case cifelse:
					printf("Command ifelse\n");
					nextNode.exp = node.command->u.cifelse.cond;
					printTree(nextNode, exp, k+1 );
					nextNode.command = node.command->u.cifelse.ifCommand;
					printTree(nextNode, command, k+1 );
					nextNode.command = node.command->u.cifelse.elseCommand;
					printTree(nextNode, command, k+1 );
					return;
				case cwhile:
					printf("Command while\n");
					nextNode.exp = node.command->u.cwhile.cond;
					printTree(nextNode, exp, k+1 );
					nextNode.command = node.command->u.cwhile.command;
					printTree(nextNode, command, k+1 );
					return;
				case cassign:
					printf("Command assign\n");
					nextNode.var = node.command->u.cassign.var;
					printTree(nextNode, var, k+1 );
					nextNode.exp = node.command->u.cwhile.exp);
					printTree(nextNode, exp, k+1 );
					return;
				case creturn:
					printf("Command return\n");
					nextNode.exp = node.command->u.returnExp;
					printTree(nextNode, exp, k+1)
					return;
				case cchamada:
					printf("Command chamada\n");
					nextNode.chamada = node.command->u.chamada;
					printTree(nextNode, chamada , k+1)
					return;
				case cbloco:
					printf("Command bloco\n");
					nextNode.bloco = node.command->u.bloco;
					printTree(nextNode, bloco, k+1)
					return;
			}
		case bloco:
			BlocoTag tag = node.bloco->tag;
			if(tag == dec) {
				printf("Bloco Dec")
				nextNode.decVar = node.bloco->u.dec;
				printTree(nextNode, decVar, k+1);
			} else {
				printf("Bloco Command")
				nextNode.command = node.bloco->u.command;
				printTree(nextNode, command, k+1);
			}
			nextNode.bloco = node.bloco->next;
			if(nextNode != NULL)
				printTree(nextNode, bloco, k+1);
			return
		case decVar:
			printf("Declaracao Var\n");
			nextNode.tipo = node.decVar->tipo;
			printTree( node.nextNode, tipo, k+1 );
			nextNode.listaNomes = node.decVar->lista;
			printTree( node.nextNode, listaNomes, k+1 );
			return;
		case listaNomes:
			printf("Lista de Nomes %s\n", node.listaNomes->id);
			nextNode.listaNomes = node.listaNomes->next;
			if(nextNode.listaNomes != NULL) 
				printTree( nextNode, listaNomes, k+1 );
			return;
		case tipo:
			TipoTag tag = node.tipo->tag;
			printf("tipo: ");
			switch(tipoTag) {
				case tint:
					printf("int");
				case tchar:
					printf("char");
				case tfloat:
					printf("float");
				case tvoid:
					printf("void");
			}
			for(i = 0; i < node.tipo->dimensions; i++) {
				printf("[]");
			}
			printf("\n")
			return;
		case param:
			printf("param: %s\n", node.param->id);
			nextNode.tipo = node.param->tipo;
			printTree( nextNode, tipo, k+1 );
			nextNode.param = node.param->next;
			if(nextNode!=NULL)
				printTree( nextNode, param, k+1 );
			return;
		case declista:
			DecTag tag = node.declista->tag;
			if(tag == decvar) {
				nextNode.decVar = node.declista->u.var;	
				printTree( nextNode, decVar, k+1 );
			} else {
				nextNode.decfunc = node.declista->u.func;
				printTree( nextNode, decfunc, k+1);
			}
			nextNode.declista = node.declista->next;
			if(nextNode!=NULL)
				printTree( nextNode, declista, k+1 );
			return;
		case decfunc:
			printf("Declaracao Func\n");
			nextNode.tipo = node.decfunc->tipo;
			printTree( node.nextNode, tipo, k+1 );
			nextNode.s = node.decfunc->id;
			printTree( node.nextNode, s, k+1 );
			nextNode.param = node.decfunc->params;
			printTree( node.nextNode, param, k+1 );
			nextNode.bloco = node.bloco;
			printTree( node.nextNode, bloco, k+1 );
			return;
		case program:
			nextNode.declista = node.program->listadec;
			printf("program\n");
			printTree( nextNode, declista, k+1 );
			return;
	}
}


int main()
{
	yyparse();
	printTree( semTree, program, 0);
	return 0;
}
