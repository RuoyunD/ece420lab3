CC=gcc
CFLAGS=-g -fopenmp

main: main.c Lab3IO.c
	$(CC) $(CFLAGS) main.c Lab3IO.c -o main

lab3io: Lab3IO.c Lab3IO.h
	$(CC) $(CFLAGS) Lab3IO.c -o lab3io

datagen: datagen.c Lab3IO.c Lab3IO.h
	$(CC) $(CFLAGS) datagen.c Lab3IO.c -o datagen

clean: 
	rm -f main lab3io datagen
