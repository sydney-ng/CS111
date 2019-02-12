CC =gcc
CCFLAGS= -Wall -Wextra

default:
	$(CC) -pthread -o lab2_add lab2_add.c
	$(CC) -pthread -g -o lab2_list lab2_list.c SortedList.c
check: 
test:
	#lab2_add with no options
	./lab2_add --threads=2 --iterations=10 >>lab2_add.csv
	./lab2_add --threads=4 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=210 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=210 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=210 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=210 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=410 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=410 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=410 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=410 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=810 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=810 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=810 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=810 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=1010 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1010 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1010 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1010 >> lab2_add.csv
	
	./lab2_add --threads=2 --iterations=10010 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10010 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10010 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10010 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100010 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100010 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100010 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100010 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=1000010 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000010 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000010 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000010 >> lab2_add.csv

	#lab2_add with yield only

	./lab2_add --threads=2 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --yield >> lab2_add.csv

	./lab2_add --threads=2 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --yield >> lab2_add.csv

	./lab2_add --threads=2 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --yield >> lab2_add.csv

	./lab2_add --threads=2 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --yield >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield >> lab2_add.csv
	
	./lab2_add --threads=2 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield >> lab2_add.csv

	./lab2_add --threads=2 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --yield >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --yield >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --yield >> lab2_add.csv
	
	#lab2_add with sync m 

	./lab2_add --threads=2 --iterations=10 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --yield --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=20 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --yield --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=40 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --yield --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=80 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --yield --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield --sync=m >> lab2_add.csv
	
	./lab2_add --threads=2 --iterations=1000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=10000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --yield --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --yield --sync=m >> lab2_add.csv

	#lab2_add with sync m 

	./lab2_add --threads=2 --iterations=10 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --yield --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=20 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --yield --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=40 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --yield --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=80 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --yield --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield --sync=s >> lab2_add.csv
	
	./lab2_add --threads=2 --iterations=1000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=10000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --yield --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --yield --sync=s >> lab2_add.csv

	#lab2_add with sync c 

	./lab2_add --threads=2 --iterations=10 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --yield --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=20 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --yield --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=40 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --yield --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=80 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --yield --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --yield --sync=c >> lab2_add.csv
	
	./lab2_add --threads=2 --iterations=1000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --yield --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=10000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --yield --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --yield --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --yield --sync=c >> lab2_add.csv

	#lab2_list with yield i 
	./lab2_list --threads=2 --iterations=10 --yield=i >> lab2_list.csv
	./lab2_list --threads=4 --iterations=10 --yield=i >> lab2_list.csv
	./lab2_list --threads=8 --iterations=10 --yield=i >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10 --yield=i >> lab2_list.csv

	./lab2_list --threads=2 --iterations=100 --yield=i >> lab2_list.csv
	./lab2_list --threads=4 --iterations=100 --yield=i >> lab2_list.csv
	./lab2_list --threads=8 --iterations=100 --yield=i >> lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=i >> lab2_list.csv
	
	./lab2_list --threads=2 --iterations=1000 --yield=i >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1000 --yield=i >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1000 --yield=i >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=i >> lab2_list.csv

	./lab2_list --threads=2 --iterations=10000 --yield=i >> lab2_list.csv
	./lab2_list --threads=4 --iterations=10000 --yield=i >> lab2_list.csv
	./lab2_list --threads=8 --iterations=10000 --yield=i >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=i >> lab2_list.csv

	./lab2_list --threads=2 --iterations=100000 --yield=i >> lab2_list.csv
	./lab2_list --threads=4 --iterations=100000 --yield=i >> lab2_list.csv
	./lab2_list --threads=8 --iterations=100000 --yield=i >> lab2_list.csv
	./lab2_list --threads=12 --iterations=100000 --yield=i >> lab2_list.csv
	
	#lab2_list with yield d
	./lab2_list --threads=2 --iterations=10 --yield=d >> lab2_list.csv
	./lab2_list --threads=4 --iterations=10 --yield=d >> lab2_list.csv
	./lab2_list --threads=8 --iterations=10 --yield=d >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10 --yield=d >> lab2_list.csv

	./lab2_list --threads=2 --iterations=100 --yield=d >> lab2_list.csv
	./lab2_list --threads=4 --iterations=100 --yield=d >> lab2_list.csv
	./lab2_list --threads=8 --iterations=100 --yield=d >> lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=d >> lab2_list.csv
	
	./lab2_list --threads=2 --iterations=1000 --yield=d >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1000 --yield=d >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1000 --yield=d >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=d >> lab2_list.csv

	./lab2_list --threads=2 --iterations=10000 --yield=d >> lab2_list.csv
	./lab2_list --threads=4 --iterations=10000 --yield=d >> lab2_list.csv
	./lab2_list --threads=8 --iterations=10000 --yield=d >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=d >> lab2_list.csv

	./lab2_list --threads=2 --iterations=100000 --yield=d >> lab2_list.csv
	./lab2_list --threads=4 --iterations=100000 --yield=d >> lab2_list.csv
	./lab2_list --threads=8 --iterations=100000 --yield=d >> lab2_list.csv
	./lab2_list --threads=12 --iterations=100000 --yield=d >> lab2_list.csv

	#lab2_list with yield il
	./lab2_list --threads=2 --iterations=10 --yield=il >> lab2_list.csv
	./lab2_list --threads=4 --iterations=10 --yield=il >> lab2_list.csv
	./lab2_list --threads=8 --iterations=10 --yield=il >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10 --yield=il >> lab2_list.csv

	./lab2_list --threads=2 --iterations=100 --yield=il >> lab2_list.csv
	./lab2_list --threads=4 --iterations=100 --yield=il >> lab2_list.csv
	./lab2_list --threads=8 --iterations=100 --yield=il >> lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=il >> lab2_list.csv
	
	./lab2_list --threads=2 --iterations=1000 --yield=il >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1000 --yield=il >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1000 --yield=il >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=il >> lab2_list.csv

	./lab2_list --threads=2 --iterations=10000 --yield=il >> lab2_list.csv
	./lab2_list --threads=4 --iterations=10000 --yield=il >> lab2_list.csv
	./lab2_list --threads=8 --iterations=10000 --yield=il >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=il >> lab2_list.csv

	./lab2_list --threads=2 --iterations=100000 --yield=il >> lab2_list.csv
	./lab2_list --threads=4 --iterations=100000 --yield=il >> lab2_list.csv
	./lab2_list --threads=8 --iterations=100000 --yield=il >> lab2_list.csv
	./lab2_list --threads=12 --iterations=100000 --yield=il >> lab2_list.csv

	#lab2_list with yield il
	./lab2_list --threads=2 --iterations=10 --yield=dl >> lab2_list.csv
	./lab2_list --threads=4 --iterations=10 --yield=dl >> lab2_list.csv
	./lab2_list --threads=8 --iterations=10 --yield=dl >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10 --yield=dl >> lab2_list.csv

	./lab2_list --threads=2 --iterations=100 --yield=dl >> lab2_list.csv
	./lab2_list --threads=4 --iterations=100 --yield=dl >> lab2_list.csv
	./lab2_list --threads=8 --iterations=100 --yield=dl >> lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=dl >> lab2_list.csv
	
	./lab2_list --threads=2 --iterations=1000 --yield=dl >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1000 --yield=dl >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1000 --yield=dl >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=dl >> lab2_list.csv

	./lab2_list --threads=2 --iterations=10000 --yield=dl >> lab2_list.csv
	./lab2_list --threads=4 --iterations=10000 --yield=dl >> lab2_list.csv
	./lab2_list --threads=8 --iterations=10000 --yield=dl >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=dl >> lab2_list.csv

	./lab2_list --threads=2 --iterations=100000 --yield=dl >> lab2_list.csv
	./lab2_list --threads=4 --iterations=100000 --yield=dl >> lab2_list.csv
	./lab2_list --threads=8 --iterations=100000 --yield=dl >> lab2_list.csv
	./lab2_list --threads=12 --iterations=100000 --yield=dl >> lab2_list.csv
graphs:
	chmod +x lab2_add.gp
	chmod +x lab2_list.gp
	./lab2_add.gp 
	#./lab2_list.gp
clean:
	rm lab2_list lab2_add lab2a-804794021.tar.gz
dist:
	tar -czvf lab2a-804794021.tar.gz README lab2_add.c lab2_list.c SortedList.c SortedList.h lab2_add.csv lab2_list.csv Makefile 