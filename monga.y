%{
	#include "tree.h"
	extern NodeProgram* semTree;
	#include <stdio.h>
	#include <malloc.h>
%}

%token	OpeningParenthesis
	ClosingParenthesis
	OpeningBracket
	ClosingBracket
	OpeningBrace
	ClosingBrace
	Comma
	SemiColon
	T_Int
	T_Char
	T_Float
	T_Void
	If
	Else
	While
	Return
	New
	Op_Assign
	Op_Minus
	Op_Plus
	Op_Multiplication
	Op_Division
	Op_Equal
	Op_LessOrEqual
	Op_GreaterOrEqual
	Op_Less
	Op_Greater
	Op_Not
	Op_And
	Op_Or
%token	<i> V_Int
%token	<c> V_Char
%token	<f> V_Float
%token	<s> V_String
%token	<s> ID

%union
{
	int i;
	char c;
	float f;
	char* s;
	struct _NodeIndexList *indexList;
	struct _NodeVar *var;
	struct _NodeExp *exp;
	struct _NodeListaExp *listExp;
	struct _NodeChamada *chamada;
	struct _NodeConst *constant;
	struct _NodeComando *command;
	struct _NodeBloco *bloco;
	struct _NodeDecVar *decVar;
	struct _NodeListaNomes *listaNomes;
	struct _NodeTipo *tipo;
	struct _NodeParam *param;
	struct _NodeDecLista *declista;
	struct _NodeDecFunc *decfunc;
	struct _NodeProgram *program;
}

%right Op_Assign
%left Op_Or
%left Op_And
%left Op_Equal
%left Op_GreaterOrEqual Op_Less Op_Greater Op_LessOrEqual
%left Op_Plus Op_Minus
%left Op_Multiplication Op_Division
%left OpeningBracket
%nonassoc Op_Not
%nonassoc IFX
%nonassoc Else

%type <exp> exp
%type <var> var
%type <indexList> index
%type <indexList> indexlista
%type <listExp> listaexp
%type <chamada> chamada
%type <constant> constant
%type <command> comando
%type <bloco> bloco%type <bloco> listabloco
%type <decVar> decvariavel
%type <listaNomes> listanomes
%type <tipo> tipo
%type <param> parametros
%type <param> parametro
%type <declista> declaracao
%type <declista> listadeclaracao
%type <decfunc> decfuncao
%type <program> programa


%start programa

%%

programa	: listadeclaracao	{ 
									$$ = (NodeProgram*) malloc(sizeof(NodeProgram));
									$$->listaDec = $1;
									semTree = $$;
									printf("End of program.\n");
								}
			;

listadeclaracao	: declaracao			{
											$$ = $1;
										}
				| listadeclaracao declaracao	{
													$$ = $1;
													$$->last->next = $2;
													$$->last = $2;
												}
				;

declaracao	: decvariavel				{
											$$ = (NodeDecLista*) malloc(sizeof(NodeDecLista));
											$$->tag = decvar;
											$$->u.var = $1;
											$$->next = NULL;
											$$->last = $$;
										}
			| decfuncao					{
											$$ = (NodeDecLista*) malloc(sizeof(NodeDecLista));
											$$->tag = func;
											$$->u.func = $1;
											$$->next = NULL;
											$$->last = $$;
										}
			;

decvariavel	: tipo listanomes SemiColon	{
											$$ = (NodeDecVar*) malloc(sizeof(NodeDecVar));
											$$->tipo = $1;
											$$->lista = $2;
										}
			;

listanomes	: ID					{ 
										$$ = (NodeListaNomes*) malloc(sizeof(NodeListaNomes));
										$$->next = NULL;
										$$->id = $1;
 									}
			| listanomes Comma ID	{ 
										$$ = (NodeListaNomes*) malloc(sizeof(NodeListaNomes));
										$$->next = $1;
										$$->id = $3;
 									}
			;

tipo	: T_Int									{
													$$ = (NodeTipo*) malloc(sizeof(NodeTipo));
													$$->tag = tint;
													$$->dimensions = 0;
												}
		| T_Char								{
													$$ = (NodeTipo*) malloc(sizeof(NodeTipo));
													$$->tag = tchar;
													$$->dimensions = 0;
												}
    	| T_Float								{
													$$ = (NodeTipo*) malloc(sizeof(NodeTipo));
													$$->tag = tfloat;
													$$->dimensions = 0;
												}
     	| T_Void								{
													$$ = (NodeTipo*) malloc(sizeof(NodeTipo));
													$$->tag = tvoid;
													$$->dimensions = 0;
												}
		| tipo OpeningBracket ClosingBracket	{
													$$ = $1;
													$$->dimensions++;
												}
     	;

decfuncao	: tipo ID OpeningParenthesis parametros ClosingParenthesis bloco
												{
													$$ = (NodeDecFunc*)malloc(sizeof(NodeDecFunc));
													$$->tipo = $1;
													$$->id = $2;
													$$->params = $4;
													$$->bloco = $6;
												}
			;

parametros	: parametro  						{
													$$ = $1;
												}
			| parametros Comma parametro 		{
													$$ = $1;
													$$->last->next = $3;
													$$->last = $3;
												}
			|									{ $$ = NULL; }

parametro	: tipo ID 							{
													$$ = (NodeParam*) malloc(sizeof(NodeParam));
													$$->tipo = $1;
													$$->id = $2;
													$$->next = NULL;
													$$->last = $$;
												}
			;

bloco	: OpeningBrace listabloco ClosingBrace  {
													$$ = $2;
												}
		;

listabloco	: decvariavel 		{ 
									$$ = (NodeBloco*) malloc(sizeof(NodeBloco));
									$$->tag = dec;
									$$->u.dec = $1;
									$$->next = NULL;
									$$->last = $$;
								}
			| comando 			{ 
									$$ = (NodeBloco*) malloc(sizeof(NodeBloco));
									$$->tag = com;
									$$->u.command = $1;
									$$->next = NULL;
									$$->last = $$;
								}

			| listabloco decvariavel
								{ 
									$$ = $1;
									$$->last->next = (NodeBloco*) malloc(sizeof(NodeBloco));
									$$->last->next->tag = dec;
									$$->last->next->u.dec = $2;
 								}
			| listabloco comando
								{
									$$ = $1;
									$$->last->next = (NodeBloco*) malloc(sizeof(NodeBloco));
									$$->last->next->tag = com;
									$$->last->next->u.command = $2; 
								}
			;

comando	: If OpeningParenthesis exp ClosingParenthesis comando Else comando
								{ 
									$$ = (NodeComando*) malloc(sizeof(NodeComando));
									$$->tag = cifelse;
									$$->u.cifelse.cond = $3;
									$$->u.cifelse.ifCommand = $5;
									$$->u.cifelse.elseCommand = $7;
 								}
		| If OpeningParenthesis exp ClosingParenthesis comando %prec IFX
								{ 
									$$ = (NodeComando*) malloc(sizeof(NodeComando));
									$$->tag = cif;
									$$->u.cif.cond = $3;
									$$->u.cif.command = $5;
 								}
		| While OpeningParenthesis exp ClosingParenthesis comando
								{ 
									$$ = (NodeComando*) malloc(sizeof(NodeComando));
									$$->tag = cwhile;
									$$->u.cwhile.cond = $3;
									$$->u.cwhile.command = $5;
 								}
		| var Op_Assign exp SemiColon
								{ 
									$$ = (NodeComando*) malloc(sizeof(NodeComando));
									$$->tag = cassign;
									$$->u.cassign.var = $1;
									$$->u.cassign.exp = $3;
 								}
		| Return exp SemiColon
								{ 
									$$ = (NodeComando*) malloc(sizeof(NodeComando));
									$$->tag = creturn;
									$$->u.returnExp = $2;
 								}
		| chamada SemiColon
								{ 
									$$ = (NodeComando*) malloc(sizeof(NodeComando));
									$$->tag = cchamada;
									$$->u.chamada = $1;
 								}
		| bloco 				{ 
									$$ = (NodeComando*) malloc(sizeof(NodeComando));
									$$->tag = cbloco;
									$$->u.bloco = $1;
 								}

		;

index	: OpeningBracket exp ClosingBracket	 	{
													$$ = (NodeIndexList*) malloc(sizeof(NodeIndexList));
													$$->exp = $2;
												}
		; 


indexlista	: indexlista index  { 
									$$ = $1;
									$$->next = $2;
 								}
			| index 			{ 
									$$ = $1;
								}

			;

var	: ID 			{
						$$ = (NodeVar*)malloc(sizeof(NodeVar));
						$$->id = $1;
						$$->indexList = NULL;
					}

	| ID indexlista	{
						$$ = (NodeVar*)malloc(sizeof(NodeVar));
						$$->id = $1;
						$$->indexList = $2;
					}
	;

constant	: V_Int		{
							$$ = (NodeConst*)malloc(sizeof(NodeConst));
							$$->tag = vint;
							$$->u.i = $1;
						}
			| V_String	{
							$$ = (NodeConst*)malloc(sizeof(NodeConst));
							$$->tag = vstring;
							$$->u.s = $1;
						}
			| V_Float	{
							$$ = (NodeConst*)malloc(sizeof(NodeConst));
							$$->tag = vfloat;
							$$->u.f = $1;
						}
			| V_Char	{
							$$ = (NodeConst*)malloc(sizeof(NodeConst));
							$$->tag = vchar;
							$$->u.c = $1;
						}
			;

chamada	: ID OpeningParenthesis listaexp ClosingParenthesis 	
												{
													$$ = (NodeChamada*)malloc(sizeof(NodeChamada));
													$$->id = $1;
													$$->parans = $3;
												}
		;

listaexp	: listaexp Comma exp 				{
													$$ = (NodeListaExp*)malloc(sizeof(NodeListaExp));
													$$->list = $1;
													$$->exp = $3;
												}	
			| exp 								{
													$$ = (NodeListaExp*)malloc(sizeof(NodeListaExp));
													$$->exp = $1;
													$$->list = NULL;
												}
			;

exp	: constant									{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = constantExp;
													$$->u.k = $1;
												}
	| var 										{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = varExp;
													$$->u.var = $1;
												}
	| OpeningParenthesis exp ClosingParenthesis {
													$$ = $2; 
												}
	| chamada  									{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = chamadaExp;
													$$->u.chamada = $1;
												}
	| Op_Minus exp 								{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = unMinusExp;
													$$->u.unary_exp = $2;
												}
	| exp Op_Plus exp 							{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = addExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	| exp Op_Minus exp 							{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = minusExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	| exp Op_Multiplication exp   				{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = multiExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	| exp Op_Division exp 						{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = divExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	| exp Op_Equal exp 							{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = eqExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	| exp Op_Greater exp 						{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = greaterExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	| exp Op_Less exp 							{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = lessExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	| exp Op_GreaterOrEqual exp 				{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = GEExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	| exp Op_LessOrEqual exp 					{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = LEExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	| Op_Not exp 								{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = notExp;
													$$->u.unary_exp = $2;
												}
	| exp Op_And exp 							{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = andExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	| exp Op_Or exp 							{
													$$ = (NodeExp*)malloc(sizeof(NodeExp));
													$$->tag = orExp;
													$$->u.binary_exp.l = $1;
													$$->u.binary_exp.r = $3;
												}
	;

%%
