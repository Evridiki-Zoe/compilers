all:
	flex --outfile=test.c test.l
	gcc test.c -o test
	./test input.txt

clear:
	rm test.c
	rm test

test:
	./test input.txt

compile:
	gcc test.c -o test