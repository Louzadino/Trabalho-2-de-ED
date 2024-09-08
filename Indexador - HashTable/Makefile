all:
	@gcc -g -Wall -o main *.c -lm

run:
	@valgrind --leak-check=full ./main < entrada1.txt

clean:
	@rm -rf main