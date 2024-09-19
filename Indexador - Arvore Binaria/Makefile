all:
	@gcc -g -Wall -o main *.c -lm

run:
	@valgrind --leak-check=full ./main

clean:
	@rm -rf main