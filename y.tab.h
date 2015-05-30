
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OpeningParenthesis = 258,
     ClosingParenthesis = 259,
     OpeningBracket = 260,
     ClosingBracket = 261,
     OpeningBrace = 262,
     ClosingBrace = 263,
     Comma = 264,
     SemiColon = 265,
     T_Int = 266,
     T_Char = 267,
     T_Float = 268,
     T_Void = 269,
     If = 270,
     Else = 271,
     While = 272,
     Return = 273,
     New = 274,
     Op_Assign = 275,
     Op_Minus = 276,
     Op_Plus = 277,
     Op_Multiplication = 278,
     Op_Division = 279,
     Op_Equal = 280,
     Op_LessOrEqual = 281,
     Op_GreaterOrEqual = 282,
     Op_Less = 283,
     Op_Greater = 284,
     Op_Not = 285,
     Op_And = 286,
     Op_Or = 287,
     V_Int = 288,
     V_Char = 289,
     V_Float = 290,
     V_String = 291,
     ID = 292,
     IFX = 293
   };
#endif
/* Tokens.  */
#define OpeningParenthesis 258
#define ClosingParenthesis 259
#define OpeningBracket 260
#define ClosingBracket 261
#define OpeningBrace 262
#define ClosingBrace 263
#define Comma 264
#define SemiColon 265
#define T_Int 266
#define T_Char 267
#define T_Float 268
#define T_Void 269
#define If 270
#define Else 271
#define While 272
#define Return 273
#define New 274
#define Op_Assign 275
#define Op_Minus 276
#define Op_Plus 277
#define Op_Multiplication 278
#define Op_Division 279
#define Op_Equal 280
#define Op_LessOrEqual 281
#define Op_GreaterOrEqual 282
#define Op_Less 283
#define Op_Greater 284
#define Op_Not 285
#define Op_And 286
#define Op_Or 287
#define V_Int 288
#define V_Char 289
#define V_Float 290
#define V_String 291
#define ID 292
#define IFX 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 49 "monga.y"

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



/* Line 1676 of yacc.c  */
#line 152 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


