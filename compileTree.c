#include <stdio.h>
#include "compileTree.h"

int labelCount = 0;
int funcOffset;

int newLabel() {
	return labelCount++;
}

void compileIndexList( NodeIndexList *node ){

}

void compileExp( NodeExp *exp ){
	ExpTag etag = exp->tag;
	switch (etag)
	{
		case multiExp:
			compileAlgebricExp( exp, "imull" );
			break;
		case addExp:
			compileAlgebricExp( exp, "addl" );
			break;
		case minusExp:
			compileAlgebricExp( exp, "subl" );
			break;
		case divExp:
			compileAlgebricExp( exp, "divl" );
			break;
		case greaterExp:
			compileComparativeExp( exp );
			break;
		case lessExp:
			compileComparativeExp( exp );
			break;
		case GEExp:
			compileComparativeExp( exp );
			break;
		case LEExp:
			compileComparativeExp( exp );
			break;
		case notExp:
			compileComparativeExp( exp );
			break;
		case andExp:
			compileComparativeExp( exp );
			break;
		case orExp:
			compileComparativeExp( exp );
			break;
		case constantExp:
			compileConstant( exp->u.k );
			break;
		case varExp:
			printf("movl %d(%%ebp),%%eax\n", exp->u.var->decVar->offset);
			break;
		case chamadaExp:
			compileChamada( exp->u.chamada );
			break;
		case unMinusExp:
			compileExp( exp->u.unary_exp );
			printf("neg %%eax");
			break;
		case eqExp:
			compileComparativeExp( exp );
			break;
		case newExp:

			break;
		case castExp:
			compileExp( exp->u.castExp.exp );
			break;
	}
}

void compileListExp( NodeListaExp *listaExp ) {
	compileExp(listaExp->exp);
	printf("push %%eax\n");
	if(listaExp->next != NULL) {
		compileListExp( listaExp->next );
	}
}

void compileChamada( NodeChamada *chamada ){
	if( chamada->parans != NULL )
		compileListExp( chamada->parans );
	printf("call _%s\n", chamada->decFunc->id );
}

void compileConstant( NodeConst *constant  ){
	ConstTag ctag = constant->tag;
	switch(ctag) {
		case vint:
			printf("mov $%d, %%eax\n", constant->u.i);
			return;
		case vchar:
			printf("mov $%d, %%eax\n", constant->u.c);
			return;
		case vstring:
			// erro acho
			return;
		case vfloat:
			// erro acho
			return;
	}
}

void compileCommand( NodeComando *command ){
	ComandoTag ctag = command->tag;
	switch(ctag) {
		case cif:
		{
			int newL1 = newLabel();
			jumpFalse( command->u.cif.cond, newL1 );
			compileCommand( command->u.cif.command );
			printLabel( newL1 );
			break;
		}
		case cifelse:
		{
			int newL1 = newLabel();
			int newL2 = newLabel();
			jumpFalse( command->u.cifelse.cond, newL1 );
			compileCommand( command->u.cifelse.ifCommand );
			printf("jmp L%d\n", newL2);
			printLabel( newL1 );
			compileCommand( command->u.cifelse.elseCommand );
			printLabel( newL2 );
			break;
		}
		case cwhile:
		{
			int endLabel = newLabel();
			int startLabel = newLabel();
			printLabel( startLabel );
			jumpFalse( command->u.cwhile.cond, endLabel );
			compileCommand( command->u.cwhile.command );
			printf("jmp L%d\n", startLabel );
			printLabel( endLabel );
			break;
		}
		case cassign:
			compileExp( command->u.cassign.exp );
			printf("movl %%eax, %d(%%ebp)\n", command->u.cassign.var->decVar->offset);
			break;
		case creturn:
			compileExp( command->u.returnExp );
			printf("leave\n");
			printf("ret\n");
			break;
		case cchamada:
			compileChamada( command->u.chamada );
			break;
		case cbloco:
			compileBloco( command->u.bloco );
			break;
	}

}

void compileBloco( NodeBloco *bloco ){
	BlocoTag btag = bloco->tag;
	if(btag == dec) {
		compileDecVar( bloco->u.dec );
	} else {
		compileCommand( bloco->u.command );
	}
	if(bloco->next != NULL)
		compileBloco( bloco->next );
	return;
}

void compileDecVar( NodeDecVar *decVar ){
	printf("subl $4, %%esp\n");
	decVar->offset = funcOffset;
	funcOffset = funcOffset - 4;
	if( decVar->next != NULL ) {
		compileDecVar( decVar->next );
	}
}

void compileDeclista( NodeDecLista *declista ){
	DecTag dtag = declista->tag;
	if(dtag == decvar) {
		compileDecVar( declista->u.var );
	} else {
		compileDecfunc( declista->u.func );
	}
	if( declista->next!=NULL )
		compileDeclista( declista->next );
	return;
}

void compileDecfunc( NodeDecFunc *decfunc ){
	funcOffset = -4;
	if (decfunc->params != NULL)
		compileParam( decfunc->params, 8 );
	printf(".globl _%s\n", decfunc->id);
	printf(".def\t_%s;\t.scl\t2;\t.type 32;\t.endef\n", decfunc->id);
	printf("_%s:\n", decfunc->id);
	printf("pushl %%ebp\n");
	printf("movl %%esp, %%ebp\n");
	compileBloco( decfunc->bloco );
	printf("leave\n");
	printf("ret\n");
}


void compileParam( NodeParam *param, int offset ) {
	param->decVar->offset = offset;
	if( param->next != NULL ) {
		offset = offset + 4;
		compileParam( param->next, offset );
	}
}


void compileProgram( NodeProgram *program ){
	compileDeclista( program->listaDec );
}

void jumpFalse( NodeExp *exp, int label ) {
	ExpTag etag = exp->tag;
	switch (etag)
	{	
		case greaterExp:
			printCompare( exp );
			printf("jle L%d", label);
			break;
		case lessExp:
			printCompare( exp );
			printf("jge L%d", label);
			break;
		case GEExp:
			printCompare( exp );
			printf("jl L%d", label);
			break;
		case LEExp:
			printCompare( exp );
			printf("jg L%d", label);
			break;
		case notExp:
			jumpTrue( exp->u.unary_exp, label);
			break;
		case andExp:
			jumpTrue(exp->u.binary_exp.l, label);
			jumpTrue(exp->u.binary_exp.r, label);
			break;
		case orExp:
		{
			int newL1 = newLabel();
			jumpTrue(exp->u.binary_exp.l, newL1);
			jumpFalse(exp->u.binary_exp.r, label);
			printLabel(newL1);
			break;
		}
		case constantExp:
			if(!exp->u.k->u.i)
				printJump( label );
			break;
		case varExp:
			printf("cmp $0, %d(%%ebp)\n", exp->u.var->decVar->offset );
			printf("je L%d\n", label);
			break;
		case eqExp:
			printCompare( exp );
			printf("je L%d", label);
			break;
		case castExp:

			break;
		default:
			compileExp( exp );
			printf("or %%eax, %%eax");
			printf("jz L%d", label);
			break;
	}
}

void jumpTrue( NodeExp *exp, int label ) {
	ExpTag etag = exp->tag;
	switch (etag)
	{	
		case greaterExp:
			printCompare( exp );
			printf("jg L%d", label);
			break;
		case lessExp:
			printCompare( exp );
			printf("jl L%d", label);
			break;
		case GEExp:
			printCompare( exp );
			printf("jge L%d", label);
			break;
		case LEExp:
			printCompare( exp );
			printf("jle L%d", label);
			break;
		case notExp:
			jumpFalse( exp->u.unary_exp, label);
			break;
		case andExp:
		{
			int newL1 = newLabel();
			jumpFalse(exp->u.binary_exp.l, newL1);
			jumpTrue(exp->u.binary_exp.r, label);
			printLabel(newL1);
			break;
		}
		case orExp:
			jumpTrue(exp->u.binary_exp.l, label);
			jumpTrue(exp->u.binary_exp.r, label);
			break;
		case constantExp:
			if(exp->u.k->u.i)
				printJump( label );
			break;
		case varExp:
			printf("cmp $0, %d(%%ebp)\n", exp->u.var->decVar->offset );
			printf("jne L%d\n", label);
			break;
		case eqExp:
			printCompare( exp );
			printf("jne L%d\n", label);
			break;
		case castExp:

			break;
		default:
			compileExp( exp );
			printf("or %%eax, %%eax");
			printf("jnz L%d", label);
			break;
	}
}


void printLabel(int l) {
	printf("L%d:", l);
}

void printJump(int l) {
	printf("jmp L%d", l);
}

void printCompare( NodeExp *exp ) {
	compileExp( exp->u.binary_exp.l );
	printf("push %%eax\n");
	compileExp( exp->u.binary_exp.r );
	printf("pop %%ecx\n");
	printf("cmp %%ecx, %%eax\n");
}

void compileComparativeExp( NodeExp *exp ) {
	int newL1 = newLabel();
	int newL2 = newLabel();
	jumpFalse( exp, newL1 );
	printf("mov $1, %%eax\n");
	printf("jmp L%d\n", newL2);
	printLabel( newL1 );
	printf("mov $0, %%eax");
	printLabel( newL2 );
}

void compileAlgebricExp( NodeExp *exp, char *op ) {
	compileExp( exp->u.binary_exp.l );
	printf("push %%eax\n");
	compileExp( exp->u.binary_exp.r );
	printf("pop %%ecx\n");
	printf("%s %%ecx, %%eax\n", op);
}
