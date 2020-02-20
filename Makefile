all:
	flex --outfile=al.c al.l
	gcc al.c -o al

clear:
	rm al.c
	rm al

test:
	./al input.txt

compile:
	gcc al.c -o al