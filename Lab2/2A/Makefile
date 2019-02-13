CC =gcc
CCFLAGS= -Wall -Wextra

build:
	$(CC) -pthread -o lab2_add lab2_add.c
	$(CC) -pthread -g -o lab2_list lab2_list.c SortedList.c
check: 
tests:
	#lab2_add with no options
	./lab2_add --threads=1 --iterations=10 >>lab2_add.csv
	./lab2_add --threads=1 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=10 >>lab2_add.csv
	./lab2_add --threads=2 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv

	./lab2_add --threads=4 --iterations=10 >>lab2_add.csv
	./lab2_add --threads=4 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 >> lab2_add.csv

	# same thing but with yield
	./lab2_add --threads=1 --iterations=10 --yield >>lab2_add.csv
	./lab2_add --threads=1 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=1 --iterations=10000 --yield >> lab2_add.csv

	./lab2_add --threads=2 --iterations=10 --yield >>lab2_add.csv
	./lab2_add --threads=2 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=2 --iterations=10000 --yield >> lab2_add.csv

	./lab2_add --threads=4 --iterations=10 --yield >>lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --yield >> lab2_add.csv

	#from spec

	./lab2_add --threads=2 --iterations=10 >>lab2_add.csv
	./lab2_add --threads=4 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=20 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=40 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=80 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 >> lab2_add.csv
	
	./lab2_add --threads=2 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 >> lab2_add.csv

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

	#same thing but without yield 


	./lab2_add --threads=2 --iterations=10 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=20 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=40 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=80 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=m >> lab2_add.csv
	
	./lab2_add --threads=2 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=m >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --sync=m >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --sync=m >> lab2_add.csv

	#lab2_add with sync m 

	./lab2_add --threads=2 --iterations=10 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=20 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=40 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=80 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=s >> lab2_add.csv
	
	./lab2_add --threads=2 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=s >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100000 --sync=s >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --sync=s >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --sync=s >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --sync=s >> lab2_add.csv

	#lab2_add with sync c 

	./lab2_add --threads=2 --iterations=10 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10 --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=20 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=20 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=20 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=20 --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=40 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=40 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=40 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=40 --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=80 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=80 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=80 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=80 --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100 --sync=c >> lab2_add.csv
	
	./lab2_add --threads=2 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=1000 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=1000 --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=10000 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=10000 --sync=c >> lab2_add.csv

	./lab2_add --threads=2 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=4 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=8 --iterations=100000 --sync=c >> lab2_add.csv
	./lab2_add --threads=12 --iterations=100000 --sync=c >> lab2_add.csv

	#no yields
	./lab2_list --threads=1 --iterations=10 >>lab2_list.csv
	./lab2_list --threads=1 --iterations=100 >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 >> lab2_list.csv

	./lab2_list --threads=1 --iterations=10 --sync=m >>lab2_list.csv
	./lab2_list --threads=1 --iterations=100 --sync=m >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=m >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=m >> lab2_list.csv

	./lab2_list --threads=1 --iterations=10 --sync=m >>lab2_list.csv
	./lab2_list --threads=1 --iterations=100 --sync=m >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=m >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=m >> lab2_list.csv

	./lab2_list --threads=1 --iterations=10 --sync=m >>lab2_list.csv
	./lab2_list --threads=1 --iterations=100 --sync=m >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=m >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=m >> lab2_list.csv

	./lab2_list --threads=1 --iterations=10 --sync=s >>lab2_list.csv
	./lab2_list --threads=1 --iterations=100 --sync=s >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=s >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=s >> lab2_list.csv

	./lab2_list --threads=1 --iterations=10 --sync=s >>lab2_list.csv
	./lab2_list --threads=1 --iterations=100 --sync=s >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=s >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=s >> lab2_list.csv

	./lab2_list --threads=1 --iterations=10 --sync=s >>lab2_list.csv
	./lab2_list --threads=1 --iterations=100 --sync=s >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=s >> lab2_list.csv
	./lab2_list --threads=1 --iterations=10000 --sync=s >> lab2_list.csv

	#with yiels and sync 

	./lab2_list --threads=12 --iterations=10 --yield=i --sync=s >>lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=i --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=i --sync=s >> lab2_list.csv

	
	./lab2_list --threads=12 --iterations=10 --yield=d --sync=s >>lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=d --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=d --sync=s >> lab2_list.csv

	
	./lab2_list --threads=12 --iterations=10 --yield=il --sync=s >>lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=il --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=il --sync=s >> lab2_list.csv

	
	./lab2_list --threads=12 --iterations=10 --yield=dl --sync=s >>lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=dl --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=dl --sync=s >> lab2_list.csv

	
	./lab2_list --threads=12 --iterations=10 --yield=i --sync=m >>lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=i --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=i --sync=m >> lab2_list.csv

	
	./lab2_list --threads=12 --iterations=10 --yield=d --sync=m >>lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=d --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=d --sync=m >> lab2_list.csv

	
	./lab2_list --threads=12 --iterations=10 --yield=il --sync=m >>lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=il --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=il --sync=m >> lab2_list.csv

	
	./lab2_list --threads=12 --iterations=10 --yield=dl --sync=m >>lab2_list.csv
	./lab2_list --threads=12 --iterations=100 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=dl --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=10000 --yield=dl --sync=m >> lab2_list.csv

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

	#lab2_list with yield dl
	./lab2_list --threads=1 --iterations=10 --yield=dl >> lab2_list.csv
	./lab2_list --threads=1 --iterations=100 --yield=dl >> lab2_list.csv
	./lab2_list --threads=1 --iterations=100 --yield=dl >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 --yield=dl >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 --yield=dl >> lab2_list.csv

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

	##### tests for lab_list-4.png
	
	./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2_list.csv	
	./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2_list.csv

	./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2_list.csv
	./lab2_list --threads=1 --iterations=1000 >> lab2_list.csv

graphs:
	chmod +x lab2_add.gp
	chmod +x lab2_list.gp
	gnuplot lab2_add.gp
	gnuplot lab2_list.gp
clean:
	rm lab2_list lab2_add lab2a-804794021.tar.gz
dist:
	make 
	make tests
	make graphs
	tar -czvf lab2a-804794021.tar.gz Makefile README lab2_add.c lab2_add.csv lab2_list.c SortedList.c SortedList.h lab2_list.csv lab2_add-1.png lab2_add-2.png lab2_add-3.png lab2_add-4.png lab2_add-5.png lab2_list-1.png lab2_list-2.png lab2_list-3.png lab2_list-4.png lab2_add.gp lab2_list.gp