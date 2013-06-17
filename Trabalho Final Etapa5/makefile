name = etapa5
ifeq ($(OS),Windows_NT)
delete = del
executable = $(name).exe
else
delete = rm
executable = $(name)
endif
$(name): lex.yy.o main.o table.o parser.tab.o astree.o tac.o
		gcc -o $(name) lex.yy.o main.o table.o parser.tab.o astree.o tac.o
tac.o: tac.c
		gcc -c tac.c
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
		$(delete) main.o lex.yy.o lex.yy.c table.o parser.tab.o astree.o parser.tab.c parser.tab.h tac.o $(executable)
