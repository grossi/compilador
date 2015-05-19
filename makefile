all: flex bison monga

flex: 
	flex monga.l

bison:
	bison -dy monga.y

monga:
	realgcc.exe tree.c y.tab.c lex.yy.c -o monga.exe

tests:
	echo Testes > testes/output
	echo Expressao >> testes/output
	monga.exe < testes/testeExpressao.monga >> testes/output
	echo Comentario >> testes/output
	monga.exe < testes/testeComentario.monga >> testes/output
