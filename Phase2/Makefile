all:
	flex lex_analysis.l 
	yacc -d syntax.y
	gcc -g lex.yy.c  y.tab.c main.c -o first

clear:
	rm lex
	rm lex.yy.c
	rm first

test:
	./first
