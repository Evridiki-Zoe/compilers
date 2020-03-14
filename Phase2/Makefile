all:
	flex lex_analysis.l 
	yacc -d syntax.y
	gcc -g lex.yy.c  y.tab.c main.c -o first

test:
	./first
