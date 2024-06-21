paint.out: main.o canvas.o commands.o file.o print_statements.o paint.o
	gcc -g -Wall -Werror -o paint.out main.o canvas.o commands.o file.o print_statements.o paint.o

main.o: main.c canvas.c commands.c file.c print_statements.c paint.c
	gcc -g -Wall -Werror -c main.c

canvas.o: canvas.c canvas.h
	gcc -g -Wall -Werror -c canvas.c

commands.o: commands.c
	gcc -g -Wall -Werror -c commands.c

file.o: file.c
	gcc -g -Wall -Werror -c file.c

print_statements.o: print_statements.c
	gcc -g -Wall -Werror -c print_statements.c

paint.o: paint.c
	gcc -g -Wall -Werror -c paint.c

clean:
	rm -fr *.o *.out
