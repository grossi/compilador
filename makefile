all: flex bison monga

flex: 
	flex monga.l

bison:
	bison -dy monga.y

monga:
	gcc tree.c y.tab.c lex.yy.c -o monga.exe

testExpressao:
	monga.exe < testes/testeExpressao.monga > testes/testeExpressao.out
	diff testes/testeExpressao.expected testes/testeExpressao.out 

testComentario:
	monga.exe < testes/testeComentario.monga > testes/testeComentario.out
	diff testes/testeComentario.expected testes/testeComentario.out 

tests: testExpressao testComentario

compileTestExpressao:


compileTest: compileTestExpressao
	monga.exe < testes/testeExpressao.monga > testes/testeExpressao.s
	gcc testes/testeExpressaoMain.c -S
	cat testeExpressaoMain.s >> testes/testeExpressao.s
	rm testeExpressaoMain.s
	gcc testes/testeExpressao.s -o testesExpressao
