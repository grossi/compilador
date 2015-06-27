#include <stdio.h>
#include "tree.h"

struct _NodeTipo tipoInt = (struct _NodeTipo) {
	.tag = tint,
	.dimensions = 0,
};
struct _NodeTipo tipoChar = (struct _NodeTipo) {
	.tag = tchar,
	.dimensions = 0,
};
struct _NodeTipo tipoCharArray = (struct _NodeTipo) {
	.tag = tchar,
	.dimensions = 1,
};
struct _NodeTipo tipoFloat = (struct _NodeTipo) {
	.tag = tfloat,
	.dimensions = 0,
};
struct _NodeTipo tipoVoid = (struct _NodeTipo) {
	.tag = tvoid,
	.dimensions = 0,
};

int main()
{
	YYSTYPE startingNode;
	yyparse();
	startingNode.program = semTree;
	typifyProgram( startingNode.program );
	//printProgram( startingNode.program, 0 );
	compileProgram( startingNode.program );
	return 0;
}
