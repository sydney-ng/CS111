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
	tar -czvf lab2b-804794021.tar.gz Makefile lab2_list.c SortedList.c SortedList.h README lab2b_list.csv lab2b_1.png lab2b_2.png
profile: lab2_list
	-rm -f ./raw.gperf 
	LD_PRELOAD=/usr/local/cs/gperftools-2.7/lib/libprofiler.so.0
	CPUPROFILE=./raw.gperf ./lab2_list --threads=12 --iterations=1000 --sync=s
	pprof --text ./lab2_list ./raw.gperf >$@
	pprof --list=set_spinlock_lock ./lab2_list ./raw.gperf >> $@
	rm -f ./raw.gperf