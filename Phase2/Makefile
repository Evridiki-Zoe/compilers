all:
	flex lex_analysis.l 
	yacc -d syntax.y
	gcc -g lex.yy.c  y.tab.c main.c -o first

test:
	./first

test1:
	./first < input.txt
clear:
	rm first
	rm y.tab.c
	rm y.tab.h
	rm lex.yy.c
	rm lex.c
	
