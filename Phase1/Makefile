all:
	flex al.l
	gcc -o al main.c lex.yy.c

clear:
	rm al
	rm lex.yy.c

test:
	./al input.txt
