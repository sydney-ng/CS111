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
	"< grep 'list-id-none' lab2b_list.csv" using ($2):($3) title 'no sync' with linespoints lc rgb 'red', \
	"< grep 'list-id-s' lab2b_list.csv" using ($2):($3) title 'spinlock' with linespoints lc rgb 'green', \
	"< grep 'list-id-m' lab2b_list.csv" using ($2):($3) title 'mutex' with linespoints lc rgb 'blue' \
	 
set title "List-4: Throughput vs. number of threads for mutex synchronized partitioned lists"
set xlabel "Throughput"
set logscale x 2
set ylabel "number of threads for mutex synchronized partitioned lists"
set logscale y 10
set output 'lab2b_4.png'

# throughput = $2 
# number of threads = $3
plot \
	"< grep 'list-none-m,1,1000,1' lab2b_list.csv" using ($2):(1000000000/($7)) title 'mutex' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,2,1000,1' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,4,1000,1' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,8,1000,1' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,12,1000,1' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,1,1000,4' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,2,1000,4' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,4,1000,4' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,8,1000,4' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,12,1000,4' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,1,1000,8' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,2,1000,8' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,4,1000,8' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,8,1000,8' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,12,1000,8' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,1,1000,16' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,2,1000,16' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,4,1000,16' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,8,1000,16' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-m,12,1000,16' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \

set title "List-5: Throughput vs. number of threads for spinlock synchronized partitioned lists"
set xlabel "Throughput"
set logscale x 2
set ylabel "number of threads for mutex synchronized partitioned lists"
set logscale y 10
set output 'lab2b_5.png'

# throughput = $2 
# number of threads = $3
plot \
	"< grep 'list-none-s,1,1000,1' lab2b_list.csv" using ($2):(1000000000/($7)) title 'spinlock' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,2,1000,1' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,4,1000,1' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,8,1000,1' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,12,1000,1' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,1,1000,4' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,2,1000,4' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,4,1000,4' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,8,1000,4' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,12,1000,4' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,1,1000,8' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,2,1000,8' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,4,1000,8' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,8,1000,8' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,12,1000,8' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,1,1000,16' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,2,1000,16' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,4,1000,16' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,8,1000,16' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \
	"< grep 'list-none-s,12,1000,16' lab2b_list.csv" using ($2):(1000000000/($7)) title '' with linespoints lc rgb 'red', \

		