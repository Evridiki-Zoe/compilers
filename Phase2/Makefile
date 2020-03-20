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
	
testWorking:
	./first < phase2_tests/Working/Anonymous.asc
	./first < phase2_tests/Working/Block.asc
	./first < phase2_tests/Working/Circle.asc
	./first < phase2_tests/Working/GlobalAndLocal.asc
	./first < phase2_tests/Working/Grammar.asc
	./first < phase2_tests/Working/Random.asc
	./first < phase2_tests/Working/ShadowedNameOffunction.asc
	./first < phase2_tests/Working/Simple.asc
	./first < phase2_tests/Working/Tree.asc