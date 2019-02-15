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
set output 'lab2b_list-1.png'

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
	