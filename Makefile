all:
	flex  -o ./Compiler/lex.yy.c ./Compiler/lex_analysis.l
	yacc -d -v -o ./Compiler/y.tab.c ./Compiler/syntax.y 
	gcc -g ./Compiler/lex.yy.c ./Compiler/y.tab.c ./Compiler/main.c ./Compiler/lex.c ./Compiler/parsing.c ./Compiler/quads.c ./Compiler/targetCode.c -o alphac
	gcc -g ./VMfiles/main.c ./VMfiles/phase5.c -lm -o alpha

clean:
	rm alpha
	rm alphac
	rm -r alpha.dSYM
	rm -r alphac.dSYM
	rm ./Compiler/y.tab.c
	rm ./Compiler/y.tab.h
	rm ./Compiler/lex.yy.c
	rm ./Compiler/y.output
	rm test.bin
	
