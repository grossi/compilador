%{
	#include "y.tab.h"
	#include <math.h>
	#include <string.h>
	#include "tree.h"
	#include <stdlib.h>

	char* ProcessString(char* s)
	{
		char* processedString;
		size_t stringLength = strlen(s), processedStringLength;
		int n, deletesCount = 2, phase = 0;
		for (n = 0; n < stringLength; n++) if (s[n] == '\\' && (s[n + 1] == '\n' || s[n + 1] == '\t' ||s[n + 1] == '\\')) deletesCount++;
		 
		processedStringLength = stringLength - deletesCount;
		processedString = (char*)malloc((processedStringLength + 1) * sizeof(char));
		 
		phase++;
		for (n = 0; n < stringLength; n++)
			if (s[n + phase] == '"') processedString[n] = '\0';
			else if (s[n + phase] != '\\') processedString[n] = s[n + phase];
			else
			{
				phase++;
				if (s[n + phase] == 'n') processedString[n] = '\n';
				else if (s[n + phase] == 't') processedString[n] = '\t';
				else if (s[n + phase] == '\\') processedString[n] = '\\';
				else
				{
					processedString[n] = '\\';
					phase--;
				}
			}
	 
		return processedString;
	}

	char ProcessChar(char* c)
	{
		if (c[1] == '\\')
			if (c[2] == 'n') return '\n';
			if (c[2] == 't') return '\t';
			if (c[2] == '\\') return '\\';
		else return c[1];
	}

	char* CopyString(char* s)
	{
		int sLength = strlen(s);
		char* copy = (char*)malloc((sLength + 1) * sizeof(char));
		strcpy(copy, s);
		return copy;
	}

%}

DIGIT	[0-9]
LETTER	[a-z]|[A-Z]

%x C_COMMENT

%%

"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>.    { }

\(	return OpeningParenthesis;

\)	return ClosingParenthesis;

\[	return OpeningBracket;

\]	return ClosingBracket;

\{	return OpeningBrace;

\}	return ClosingBrace;

,	return Comma;

;	return SemiColon;

int	return T_Int;

char	return T_Char;

float	return T_Float;

void	return T_Void;

if	return If;

else	return Else;

while	return While;

return	return Return;

new	return New;

=	return Op_Assign;

\-	return Op_Minus;

\+	return Op_Plus;

\*	return Op_Multiplication;

\/	return Op_Division;

==	return Op_Equal;

\<\=	return Op_LessOrEqual;

\>\=	return Op_GreaterOrEqual;

\<	return Op_Less;

\>	return Op_Greater;

\!	return Op_Not;

&&	return Op_And;

\|\|	return Op_Or;

{DIGIT}+	{ yylval.i = strtol(yytext, NULL, 10); return V_Int; }

0x({DIGIT}|[a-f]|[A-F])+	{ yylval.i = (int)strtol(yytext, NULL, 16); return V_Int; }

'([^\\\n]|\\n|\\t|\\\\)'	{ yylval.c = ProcessChar(yytext); return V_Char; }

{DIGIT}+"."{DIGIT}*	{ yylval.f = strtof(yytext, NULL); return V_Float; }

\"[^\n]*\"	{ yylval.s = ProcessString(yytext); return V_String; }

({LETTER}|_)({LETTER}|_|{DIGIT})*	{ yylval.s = CopyString(yytext); return ID; }

[ \t\n]+	/* eat up whitespace */

.	{ return yytext[0];	}

%%

int yywrap(void)
{
   
   return 1;
}

int yyerror(void)
{
    printf("Error\n");
    exit(1);
}
