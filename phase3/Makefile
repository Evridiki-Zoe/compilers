all:
	flex lex_analysis.l
	yacc -d -v syntax.y
	gcc -g lex.yy.c y.tab.c main.c lex.c parsing.c quads.c -o first

clear:
	rm first
	rm y.tab.c
	rm y.tab.h
	rm lex.yy.c
