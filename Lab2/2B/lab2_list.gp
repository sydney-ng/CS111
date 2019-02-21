#! /usr/bin/gnuplot
#
# purpose:
#	 generate data reduction graphs for the multi-threaded list project
#
# input: lab2b_list.csv
#	1. test name
#	2. # threads
#	3. # iterations per thread
#	4. # lists
#	5. # operations performed (threads x iterations x (ins + lookup + delete))
#	6. run time (ns)
#	7. run time per operation (ns)
set terminal png
set datafile separator ","

set title "List-1: Mutex & Spinlock - Throughput vs. Thread Nums"
set xlabel "Thread Nums"
set logscale x 2
set ylabel "Throughput"
set logscale y 10
set output 'lab2b_1.png'

# throughput = $6 
# number of threads = $2
plot \
     "< grep 'list-none-s,1,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title 'spinlock' with linespoints lc rgb 'red', \
	 "< grep 'list-none-s,2,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-none-s,4,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'red', \
 	"< grep 'list-none-s,8,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-none-s,12,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-none-s,16,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-none-s,24,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,1,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,2,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,4,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'green', \
 	"< grep 'list-none-m,8,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,12,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,16,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,24,' lab2b_list.csv" using ($2):(1000000000/$6) \
	title '' with linespoints lc rgb 'green', \

set title "List-2: Mutex Wait for Lock vs. Time/Operation"
set xlabel "Thread Nums"
set logscale x 2
set ylabel "Throughput"
set logscale y 10
set output 'lab2b_2.png'

# throughput = $6 
# number of threads = $2
plot \
     "< grep 'list-none-s,1,' lab2b_list.csv" using ($2):($7) \
	title 'mutex' with linespoints lc rgb 'red', \
	 "< grep 'list-none-s,2,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-none-s,4,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'red', \
 	"< grep 'list-none-s,8,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-none-s,12,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-none-s,16,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-none-s,24,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,1,' lab2b_list.csv" using ($2):($7) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,2,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,4,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'green', \
 	"< grep 'list-none-m,8,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,12,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,16,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-none-m,24,' lab2b_list.csv" using ($2):($7) \
	title '' with linespoints lc rgb 'green', \

set title "List-3: successful iterations vs. threads for each synchronization "
set xlabel "Successful Iterations"
set logscale x 2
set ylabel "Threads for Synchronization"
set logscale y 10
set output 'lab2b_3.png'

# throughput = $2 
# number of threads = $3
plot \
	 "< grep 'list-id-none,1,1,' lab2b_list.csv" using ($2):($3) \
	title 'no sync' with linespoints lc rgb 'red', \
	"< grep 'list-id-none,1,2,' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \
	"< grep 'list-id-none,1,4,' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \ 
	"< grep 'list-id-none,1,8,' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \ 
	"< grep 'list-id-none,1,16' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-id-none,4,1' lab2b_list.csv" using ($2):($3) \
	title 'no sync' with linespoints lc rgb 'red', \
	 "< grep 'list-id-none,4,2' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \
 	"< grep 'list-id-none,4,4' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \ 
	"< grep 'list-id-none,4,8' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \ 
	"< grep 'list-id-none,4,16' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-id-none,8,1' lab2b_list.csv" using ($2):($3) \
	title 'no sync' with linespoints lc rgb 'red', \
	 "< grep 'list-id-none,8,2' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \
 	"< grep 'list-id-none,8,4' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \ 
	"< grep 'list-id-none,8,8' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \ 
	"< grep 'list-id-none,8,16' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-id-none,8,1' lab2b_list.csv" using ($2):($3) \
	title 'no sync' with linespoints lc rgb 'red', \
	 "< grep 'list-id-none,8,2' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \
 	"< grep 'list-id-none,8,4' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \ 
	"< grep 'list-id-none,8,8' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \ 
	"< grep 'list-id-none,8,16' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \
	 "< grep 'list-id-none,16,1' lab2b_list.csv" using ($2):($3) \
	title 'no sync' with linespoints lc rgb 'red', \
	 "< grep 'list-id-none,16,2' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \
 	"< grep 'list-id-none,16,4' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \ 
	"< grep 'list-id-none,16,8' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \ 
	"< grep 'list-id-none,16,16' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'red', \


	 "< grep 'list-id-m,1,10' lab2b_list.csv" using ($2):($3) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,1,20' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,1,40' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,1,80' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	"< grep 'list-id-m,4,10' lab2b_list.csv" using ($2):($3) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,4,20' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,4,40' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,4,80' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	"< grep 'list-id-m,8,10' lab2b_list.csv" using ($2):($3) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,8,20' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,8,40' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,8,80' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	"< grep 'list-id-m,12,10' lab2b_list.csv" using ($2):($3) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,12,20' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,12,40' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,12,80' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	"< grep 'list-id-m,16,10' lab2b_list.csv" using ($2):($3) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,16,20' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,16,40' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-m,16,80' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \


	"< grep 'list-id-s,1,10' lab2b_list.csv" using ($2):($3) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,1,20' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,1,40' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,1,80' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	"< grep 'list-id-s,4,10' lab2b_list.csv" using ($2):($3) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,4,20' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,4,40' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,4,80' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	"< grep 'list-id-s,8,10' lab2b_list.csv" using ($2):($3) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,8,20' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,8,40' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,8,80' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	"< grep 'list-id-s,12,10' lab2b_list.csv" using ($2):($3) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,12,20' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,12,40' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,12,80' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	"< grep 'list-id-s,16,10' lab2b_list.csv" using ($2):($3) \
	title 'mutex' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,16,20' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,16,40' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
	 "< grep 'list-id-s,16,80' lab2b_list.csv" using ($2):($3) \
	title '' with linespoints lc rgb 'green', \
