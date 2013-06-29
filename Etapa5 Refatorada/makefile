name = test
yacc = bison
lex = flex
compile-c = gcc -c -Wall -pedantic
compile-o = gcc -o
ifeq ($(OS),Windows_NT)
delete = del
executable = $(name).exe
else
delete = rm
executable = $(name)
endif
$(name) : main.o hash.o parser.tab.o lex.yy.o astree.o semantic.o tac.o assembler.o
	$(compile-o) $(name) main.o hash.o parser.tab.o lex.yy.o astree.o semantic.o tac.o assembler.o
assembler.o : assembler.c
	$(compile-c) assembler.c
tac.o : tac.c parser.tab.h
	$(compile-c) tac.c
semantic.o : semantic.c parser.tab.h
	$(compile-c) semantic.c
main.o : main.c
	gcc -c main.c
hash.o : hash.c parser.tab.h
	$(compile-c) hash.c
astree.o : astree.c parser.tab.h
	$(compile-c) astree.c
parser.tab.o :	parser.tab.c
	gcc -c parser.tab.c
lex.yy.o : lex.yy.c parser.tab.h
	gcc -c lex.yy.c	
parser.tab.c parser.tab.h: parser.y
	$(yacc) -d parser.y	
lex.yy.c : scanner.l
	$(lex) scanner.l
clean:
	$(delete) hash.o main.o lex.yy.o parser.tab.o parser.tab.h $(executable) astree.o lex.yy.c parser.tab.c semantic.o tac.o assembler.o