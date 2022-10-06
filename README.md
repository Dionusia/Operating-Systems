# Operating-Systems

QUESTIONS

Question A [25]: (A) Create a program in which a process in Linux/Unix spawns N more of its children. Each process i (1<=i<=N), reads the value stored in the root of a shared Heap tree (min heap or max heap, it doesn't matter) which stores 10N discrete integers in the interval [1, 10N ], and then adds it to a shared variable int *p, initialized to 0. For example, if N=10, then the shared memory heap-tree stores all distinct numbers in the interval [1, 100], i.e. 1,2,3, …..,99, 100. The heap is accessible from the shared root pointer. Synchronize the above processes so that at the end the variable p contains the sum of the values ​​of all the distinct numbers in the interval [1, 10N]. What is the total time to calculate the above sum? (B) If the Heap tree is not shared, does the same result occur? What do you notice about the total computation time?

***Count CPU cycles using the clock() function. Then divide by the built-in constant CLOCKS_PER_SEC to get the number of seconds.

Question B [20]: Write a program that uses semaphores to solve the problem of readers and writers to avoid deadlock. That is, if there is a desire for both subscribers and readers to access the database at the same time, they will access it alternately, one by one, for example, first a reader, then a subscriber, then again a reader, etc. .K.

Question C [10]: In a program in the OS kernel, 5 system calls are made (Systems Calls: SC1, SC2, SC3, SC4 and SC5). SC1, SC2 and SC3 commands are executed first (they are the initial activities of the program) and can be executed in parallel (in any order). The SC4 command can only be started when the SC1 and SC2 commands have finished executing. SC5 is the final command of the program and can only be started when the SC3 and SC4 commands have finished executing.

You are asked to implement code that represents (with maximum possible parallelism) the execution order of the system calls of the above program. Don't forget to declare and initialize the semaphores you will use.

Consider that each SC1...SC5 command executes a system command of your choice. e.g. system("ls -l") or system("ps -l") etc...
