CC =gcc
CCFLAGS= -Wall -Wextra

simpsh: lab1a.o
	$(CC) -o simpsh lab1a.o
lab1a.o: lab1a.c
	$(CC) -c lab1a.c
check: 
	./smoketest.sh

clean: 
	rm simpsh lab1a.o lab1-804794021.tar.gz
dist: 
	tar -czvf lab1-804794021.tar.gz README lab1a.c  Makefile 
