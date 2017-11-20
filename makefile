all: pipe.c
	gcc -o piping pipe.c
clean:
	rm a.out
	rm piping
	rm *~
run: all
	./piping

