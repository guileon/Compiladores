target: etapa5

etapa5: lex.yy.o hash.o main.o y.tab.o astree.o declarations.o sintaxe.o semanticaSegundaPAssada.o genco.o tac.o
	gcc -o etapa4 lex.yy.o hash.o main.o y.tab.o astree.o declarations.o sintaxe.o semanticaSegundaPAssada.o

etapa4: lex.yy.o hash.o main.o y.tab.o astree.o declarations.o sintaxe.o semanticaSegundaPAssada.o
	gcc -o etapa4 lex.yy.o hash.o main.o y.tab.o astree.o declarations.o sintaxe.o semanticaSegundaPAssada.o

etapa3: lex.yy.o hash.o main.o y.tab.o astree.o
	gcc -o etapa3 lex.yy.o hash.o main.o y.tab.o astree.o

tac.o:
	gcc -c tac.c
	
genco.o:
	gcc -c genco.c
	
SemanticaSegundaPAssada.o:
	gcc -c semanticaSegundaPAssada.c

sintaxe.o: sintaxe.c
	gcc -c sintaxe.c

declarations.o:	declarations.c
	gcc -c declarations.c

astree.o: astree.c astree.h
	gcc -c astree.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c:
	yacc -v parser.y --debug --verbose
y.tab.h:
	yacc -d parser.y

main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l y.tab.h
	flex --header-file=lex.yy.h scanner.l 



######## clean

clean:
	rm -f *.o lex.yy.c lex.yy.h y.tab.c y.tab.h etapa2 hashTest
