CC =gcc
CCFLAGS= -Wall -Wextra

simpsh: lab1b.o
	$(CC) -o simpsh lab1b.o
lab1b.o: lab1b.c
	$(CC) -c lab1b.c
check: 
	-./test.sh
clean: 
	rm simpsh lab1b.o lab1-804794021.tar.gz
dist: 
	tar -czvf lab1-804794021.tar.gz README report.pdf lab1b.c test.sh Makefile 
