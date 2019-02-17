CC =gcc
CCFLAGS= -Wall -Wextra

build:
	$(CC) -ltcmalloc -lprofiler -pthread -g -o lab2_list lab2_list.c SortedList.c
tests:
	#picture # 1 
	#synchronized spinlock 
	./lab2_list --threads=1 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=s >> lab2b_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=s >> lab2b_list.csv
	#synchronized mutex 	
	./lab2_list --threads=1 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=2 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=4 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=8 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=12 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=16 --iterations=1000 --sync=m >> lab2b_list.csv
	./lab2_list --threads=24 --iterations=1000 --sync=m >> lab2b_list.csv
	
graphs:
	chmod +x lab2_list.gp
	gnuplot lab2_list.gp
clean:
	rm lab2_list lab2a-804794021.tar.gz
dist:
	make 
	make tests
	make graphs
	tar -czvf lab2a-804794021.tar.gz Makefile lab2_list.c SortedList.c
profile: 
	CPUPROFILE=./profile_1.out ./lab2_list --threads=12 --iterations=1000 --sync=s
	pprof --text ./lab2_list ./profile_1.out >> profile_2.out
	pprof --list=set_spinlock_lock ./lab2_list ./profile_1.out >> profile.out