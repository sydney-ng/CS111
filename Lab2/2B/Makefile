CC =gcc
CCFLAGS= -Wall -Wextra

build:
	$(CC) -ltcmalloc -lprofiler -pthread -g -o lab2_list lab2_list.c SortedList.c
tests:
	#picture # 1 
	#synchronized spinlock 
	-./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2b_list.csv
	#synchronized mutex 	
	-./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2b_list.csv

	#picture 3
		#no sync
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=2 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=2 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=2 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=2 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=16 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=1 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=2 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=4 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=8 >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=16 >> lab2b_list.csv
		#with mutex sync
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=10 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=20 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=40 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=80 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=10 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=20 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=40 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=80 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=10 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=20 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=40 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=80 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=10 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=20 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=40 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=80 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=10 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=20 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=40 --sync=m >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=80 --sync=m >> lab2b_list.csv
		#with spinlock sync
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=10 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=20 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=40 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=1 --iterations=80 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=10 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=20 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=40 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=4 --iterations=80 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=10 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=20 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=40 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=8 --iterations=80 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=10 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=20 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=40 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=12 --iterations=80 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=10 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=20 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=40 --sync=s >> lab2b_list.csv
	-./lab2_list --yield=id --lists=4 --threads=16 --iterations=80 --sync=s >> lab2b_list.csv
	#for mutex picture 4 
	-./lab2_list --lists=1 --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=8 --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=16 --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=1 --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=8 --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=16 --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=1 --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=8 --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=16 --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=1 --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=8 --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=16 --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=1 --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=8 --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	-./lab2_list --lists=16 --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	#picture 5 (spinlock)
	-./lab2_list --lists=1 --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=8 --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=16 --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=1 --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=8 --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=16 --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=1 --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=8 --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=16 --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=1 --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=8 --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=16 --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=1 --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=4 --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=8 --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	-./lab2_list --lists=16 --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
		

graphs:
	chmod +x lab2_list.gp
	gnuplot lab2_list.gp
clean:
	rm lab2_list lab2b-804794021.tar.gz
dist:
	make 
	make tests
	make graphs
	make profile
	tar -czvf lab2b-804794021.tar.gz Makefile profile.out lab2_list.c SortedList.c SortedList.h README lab2b_list.csv lab2b_1.png lab2b_2.png lab2b_3.png lab2b_4.png lab2b_5.png lab2_list.gp
profile: lab2_list
	CPUPROFILE=./profile_1.out ./lab2_list --threads=12 --iterations=1000 --sync=s
	pprof --text ./lab2_list ./profile_1.out >> profile_2.out
	pprof --list=set_spinlock_lock ./lab2_list ./profile_1.out >> profile.out
	rm profile_1.out 
	rm profile_2.out