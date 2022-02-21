#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <time.h>           /*clock(),clock_t*/
#include <unistd.h>


#define ONE 1

typedef sem_t      Semaphore;

Semaphore *mutex;  //synch semaphore
////////////////////////////////////////////////////////////////////////////////
int size = 0;
void swap(int *a, int *b)
{
  int temp = *b;
  *b = *a;
  *a = temp;
}

void heapify(int array[], int size, int i)
{
  if (size == 1)
  {
    printf("Single element in the heap");
  }
  else
  {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && array[left] > array[largest])
      largest = left;
    if (right < size && array[right] > array[largest])
      largest = right;
    if (largest != i)
    {
      swap(&array[i], &array[largest]);
      heapify(array, size, largest);
    }
  }
}

void insert(int array[], int newNum)
{
  if (size == 0)
  {
    array[0] = newNum;
    size += 1;
  }
  else
  {
    array[size] = newNum;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
      heapify(array, size, i);
    }
  }
}
    

////////////////////////////////////////////////////////////////////////////////

int main ()
{
    clock_t start_t, end_t, total_t;      //clock veriables
    int i;                                // loop variables
    key_t shmkey;                         //shared memory key 
    int shmid;                            // shared memory id  
    int shmidarr;                         //shared memory id for the array  
    pid_t pid;                            // fork pid                  
    int *p;                               // shared variable            
    int n;                                //fork count                
    int *heap;                           //the shared heap
	int SizeMem;              
	
	
	//starting time
	start_t = clock();
    
    	
    //arxikopoihsh a shared variable in shared memory
    //valid directory name and a number
    shmkey = ftok ("/dev/null", 5);       
    shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
    //arxikopoihsh tou shared array se shared memory 
    SizeMem = sizeof(*heap)*n;
    shmidarr = shmget(shmkey, n*sizeof(int), IPC_CREAT);
    /* sundesh array me to shared memory */
    heap = (int *)shmat(shmidarr, 0, 0);
    heap = malloc(sizeof(int)*(n*10));
    
    

	// shared memory error 
    if (shmid < 0 && shmidarr < 0)                           
    {
        perror ("shmget\n");
        exit (1);
    }
							       
	/* sundesi toy p me to shared memory */
    p  = (int *) shmat (shmid, NULL, 0);   
    *p = 0;

    printf ("How many children do you want to fork?\n");
    printf ("Fork count: ");
    scanf  ("%u", &n);
    
    for(i=0;i<=10*n;i++){
        insert(heap,i);
    }

    //arxikopoihsh semaphores for shared processes 
    mutex = sem_open ("pSem", O_CREAT | O_EXCL, 0644, ONE); 


    
    //fork child process
    for (i = 0; i <=10*n; i++)
    {
        pid = fork ();
     
	    if (pid < 0) {
        // check for error
            sem_unlink ("pSem");   
            sem_close(mutex);  

            /* unlink prevents the semaphore existing forever */
            /* if a crash occurs during the execution         */
            printf ("Fork error.\n");
        }
        else if (pid == 0) /* child processes */
            break;                  
    }


    //parent process
    if (pid > 0)
	{
        //  wait for all children to exit
        while (pid = waitpid (-1, NULL, 0))
        {
            if (errno == ECHILD)
                break;
        }

        printf (" Parent: All children have exited.\n");
		printf (" *p = %d\n\n\n", *p);
		
        // shared memory detach
        shmdt (p);
        shmctl (shmid, IPC_RMID, 0);

        //unlink prevents the semaphore existing forever
        sem_unlink ("pSem");   
        sem_close(mutex);  
    }
    //child process
    else
	{
        sem_wait (mutex);  
        *p=*p+heap[i];
        
        sleep (1);
        printf ("Child(%d) increasing *p\n",i);
		printf (" new value of *p=%d.\n", *p);
		
		
        sem_post (mutex);           
    }

   
    
   end_t = clock();
   printf("Starting of the program is, start_t = %ld\n", start_t);
   printf("End of the processe, end_t = %ld\n", end_t);
   printf("Exiting of the program...\n");
   
   exit(0);
}





