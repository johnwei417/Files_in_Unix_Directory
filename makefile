all:
	gcc -Wall -Wpedantic -std=c99 *.c -g -o 3240Assignment2

test:
	./3240Assignment2 < .
