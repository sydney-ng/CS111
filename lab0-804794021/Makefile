CC =gcc
CCFLAGS= -Wall -Wextra

lab0: lab0.o
	$(CC) -o lab0 lab0.o
lab0.o: lab0.c
	$(CC) -c lab0.c
check: 
	-./smoketest.sh
clean: 
	rm lab0 lab0.o lab0-804794021.tar.gz
dist: 
	tar -czvf lab0-804794021.tar.gz lab0.c smoketest.sh Makefile backtrace.png breakpoint.png README
