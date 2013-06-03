name = etapa4
$(name): lex.yy.o main.o table.o parser.tab.o astree.o hex.o
		gcc -o $(name) lex.yy.o main.o table.o parser.tab.o hex.o astree.o
		
parser.tab.o: parser.tab.c
		gcc -c parser.tab.c
lex.yy.o: lex.yy.c  parser.tab.h
		gcc -c lex.yy.c
main.o: main.c
		gcc -c main.c
table.o: table.c
		gcc -c table.c
astree.o: astree.c astree.h parser.tab.h
		gcc -c astree.c
parser.tab.c parser.tab.h: parser.y
		bison -d parser.y
lex.yy.c: scanner.l
		flex scanner.l
clean:
		del main.o lex.yy.o lex.yy.c table.o parser.tab.o parser.tab.c parser.tab.h $(name) del astree.o
		rm $(name).exe rm main.o lex.yy.o lex.yy.c table.o parser.tab.o astree.o parser.tab.c parser.tab.h $(name) rm $(name).exe
