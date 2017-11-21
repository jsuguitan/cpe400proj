CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

sim : main.o 
	$(CC) $(LFLAGS) main.o -o main

main.o : main.cpp 
	$(CC) $(CFLAGS) main.cpp 

clean: 
	\rm *.o sim