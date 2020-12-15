# CS111

## UCLA's CS111 - Operating Systems 
## Operating System Principles
### Professor: Paul Eggert
### Quarter: Winter 2019

Operating System Principles is meant to lay the foundation for a solid grounding in the basic principles of operating system design.  
This grounding is critical in a deeper understanding of how a vital piece of system software operates and introduce you to important concepts that are frequently used in large software systems you are likely to encounter in your future work. 

## Skills Demonstrated 
All of the projects have been coded in C. Shell scripts have been created to interact with the code. Each project has a makefile that I have specifically written for that project.

# Projects 
Description of the following work: 

## Lab 1

This project will use file descriptors that will either only open/ only write to, execute a command to a specific file descriptor, and possibly print out the commands you’re executing (if the user asks for it). You also can combine these together. Error messages will be printed to the error file descriptor if errors are encountered. In part 1B, we can support all the commands except for --profile. We support more opening/closing options & are able to retrieve the arguments of a command using --wait. In Part 1C, we are adding the ability to use the —-profile option so that you may track the amount of time that it takes to execute a command or it’s children processes. You also will have the ability to see the amount of time that is being spent in the user process. 

Limitations of Code: 
- If you have a process where you close the read/write pipe file descriptors wrong (ex. You call close, but the parent’s write end of the pipe hasn’t been closed yet), your program will hang forever. This was an issue that I ran into when writing the code to pass test case #17. However, if you pass in an argument that closes the file descriptors in the wrong order, there is no catch mechanism to warn you or have a safe failout.

Here are some of the sources that I used while completing this project:
- How to use pipes: https://www.tldp.org/LDP/lpg/node11.html
- How to use getopt: https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
- How to use Timeval: https://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html

## Lab 2A  

This is a project that uses different methods of synchronizations such as locks to examine how they affect the accuracy and scalability of a program. For this example, we examine mutexes, spin locks, and compare and swap locks and how it is used to preserve the integrity of the data when we have many threads or iterations. We also look at the affect that yielding has on the outcome of the processes and how that affects the distribution and timing of resources.  

QUESTION 2.1.1 - causing conflicts:
	It takes about 10000 iterations and you will begin to see errors. You’ll see less errors on smaller iterations because there is less competition for resources. Just by the principles of probability, if you exponentially increase the amount of error that could happen when 2 (or in this case 10000 computations are trying to happen as synchronously as possible.
QUESTION 2.1.2 - cost of yielding:
	Yield is significantly slower because according to the man page for sched_yield(), this function “causes the calling thread to relinquish the CPU”. There is a context switch forcing the processor to complete the tasks for another thread. For smaller programs, this doesn’t have as large of an affect because the overhead is proportionally smaller. When you have many iterations, however, this increase in the number of context switching exponentially affects the runtimes.The man pages specify that the current thread is put at the “end of the queue for its static priority and a new thread gets to run”. This means that there is a context switch. During this context switch, it takes time to process an interrupt, save all the values from the context of that process (ex. caches, stack, registers). You also are switching from user to kernel mode and asking the scheduler to rearrange the order in which the threads will be processes. All of these steps require time, and when you multiply this by N number of threads, the additional time will increase exponentially. No, it is not possible to get valid per-operation timings. When you call yield, you are asking the scheduler to switch from your current process to another. However, when you do this, you are adding time for the interrupts, switching form user to kernel mode, and all of the steps that were mentioned in 2.1.2.2. This is taken account into the total runtime that we use to get the per-operation timings. Also, when you are doing this type of operations, the processor may not be able to use all of the optimizations it otherwise would if it had more resources for a longer period of time (therefore also increasing the time that it takes for that thread job to complete). 
QUESTION 2.1.3 - measurement errors:
	The average cost per operation will drop with increasing iterations because there is a large overhead that is associated with created a thread. Each time you create a thread, you need to create and save variables that correspond with the program resources and execution state. In addition, each thread has its own stack pointer, registers, scheduling priorities, and signal statuses. Threads that are in the same process can share resources, but they still operate independently so it is still costly. Therefore, if you can maximize the number of iterations that you are doing, you can help balance out these costs. Eventually, the graph levels out after ___number of iterations. You can then use simple math to do (upper bound number of iterations - lower bound number of iterations)/(time 2 - time 1). This would give you a close number . 
QUESTION 2.1.4 - costs of serialization:
	When you have low number of threads, there is less competition to get the lock. Therefore, this increases the probability that you will get the lock from the program. However, when you increase the number of threads, there are more race conditions. This is more opportunity for calculations to  happen not synchronously. The protected operations slow down as the number of threads rises because you have lots of threads that need to use the lock. Once a thread has hold of a lock, it will not relinquish it until the operation that needs to be performed has been completed. Therefore, if you have lots of threads that are holding the lock, you will see the efficiency and speed of the program dramatically decrease. 
QUESTION 2.2.1 - scalability of Mutex:
	Time per mutex-protected operation seems to be a lot slower in Part 1. This is because in the second part, we are multiplying the number of threads x iterations by 3 since we have to lookup,  delete, and insert. This increases the number of operations that occur (while the first part only had threads x iterations). By adding more steps, this will make the mutex-protected operations a lot faster. 
	QUESTION 2.2.2 - scalability of spin locks: 
	In the beginning the shapes of the curves look very similar for mutex and spinlocks. This is because there are not many race conditions as there aren’t that many threads that need to acquire the lock. However, when we increase the number of threads, this is when we can see the difference. While this wouldn’t matter much in the beginning when there are not many threads, spinlocks repeatedly check to see if it can grab the lock and this content checking multiplied by a large number of threads will make it take a long time. Mutexes work more straightforwardly with just a simple lock and unlock. In the beginning, again this may be more costly (and therefor similar to using a spinlock). However, if you have a lot of threads, it is useful to just have this straightforward method instead of having to check each time. We can see this reflected in the curve of the graph with Mutex completing faster.
  
  
 ## Lab 2B 

This is a project that uses different methods of synchronizations such as locks to examine how they affect the accuracy and scalability of a program. For this example, we examine mutexes, spin locks, and compare and swap locks and how it is used to preserve the integrity of a linked list when we have many threads or iterations. We also look at the affect that yielding has on the outcome of the processes and how that affects the distribution and timing of resources.  

QUESTION 2.3.1 - CPU time in the basic list implementation:
	There are 8 different cases to consider for this question. If there is 1 thread and small number of iterations or large number of iterations for spinlock, majority of the time will be spent in the list operation as there is only 1 thread to do the computation and there is no wait time. The one thread will always be able to obtain the resource. For 2 threads and small number of iterations or large number of iterations for spinlock, half the time will be spent in spinning and the other half will be in the liste operations. This is because whenever one thread is doing the computation, the other thread has to spin. The number of iterations doesn't matter becuase the graph will just look the same, just longer because one thread will always be waiting. If there is 1 thread or 2 threads and a small number of iterations for mutex, we there is no way of knowing exactly where the time is spent. We don't have a way to record how fast the mutex is obtained and released & even if we did, this number could be not accurate. If there is 1 thread or 2 threads and a large number of iterations for mutex, majority of the time will be spent in completing the list operation because there are many nodes that we need to traverse and check through. 
QUESTION 2.3.2 - Execution Profiling:
	My set_spinlock_lock function took the most amount of time when the spin-lock version of the list exerciser is run with a large number of threads. This is because this parent function is the one that will call __sync_lock_test_and_set_ and will also eventually call __sync_lock_release, so many locks spend a lot of time in this function when they are between stages of doing the computation. This happens before the insert, length, and lookup/delete operations, which is why this time is multiplied by three. 
QUESTION 2.3.3 - Mutex Wait Time:
	The average lock-wait time rises dramatically with the number of contending threads because you have more threads competeing for the same resources. Because one thread has the lock, the rest of the threads must wait, so if you have more threads, that's more threads waiting. The completion time per operation also rises with the number of contending threads because the wall time will add up when you have 8 or 16 threads, giving you a higher completion time. However, because completion time doesn't include wait time, it is possible for you to have the wait time per operation to go up faster (or higher) than the completion time per operation. 
QUESTION 2.3.4 - Performance of Partitioned Lists: 
	In terms of performance, you're splitting up the lists into smaller lists so that you can use a simple hashing function to find out what smaller list it is in. This decreases the lookup, insertion, and length calculation time. The throughput would continue increasing as the number of lists is further increased because you would be doing what was said above. However, this eventually would level off because you'll just have one element in every sub-list. An N-way partitioned list should be equivalent to the throughput of a single list with fewer (1/N) threads becuase the number of sublists is directly correlated with the number of threads that have been created in a specific process. However, this is not reflected in the curves.
  
  
 ## Lab 3
 
 We are all familiar with the characteristics of the files and directories in which we store all of our data. As with many other persistent objects, their functionality, generality, performance and robustness all derive from the underlying data structures used to implement them. In this project we will design and implement a program to read the on-disk representation of a file system, analyze it, and summarize its contents. In the next project, we will write a program to analyze this summary for evidence of corruption.
This project shows the knowledge of the different aspects of the basic file system concepts of directory objects, file objects, and free space. 
We were researching, examining, interpreting and processing information in complex binary data structures. We had to examine and interpret and raw hex dumps of complex data structures as a means of developing an understanding of those data structures.
We worked with typical on-disk file system data formats to complete this project. 


## Lab 4 

In this project, we investiaged how limited CPU power greatly restricts possible processing, how limited memory greatly restricted the type of software that could be run.
The available libraries were minimal, and mostly device related. Development had to be done on another system, cross-compiled, and then up-loaded and flashed onto the Arduino.
