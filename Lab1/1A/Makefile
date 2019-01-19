CC =gcc
CCFLAGS= -Wall -Wextra

simpsh: lab1a.o
	$(CC) -o lab1a lab1a.o
lab1a.o: lab1a.c
	$(CC) -c lab1a.c
check: 
clean: 
	rm simpsh lab1a.o lab1-804794021.tar.gz
dist: 
	tar -czvf lab1-804794021.tar.gz lab1a.c  Makefile 
