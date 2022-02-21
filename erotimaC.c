#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h>

//tha xrhsimopoihsw 2 semaphorous
sem_t s1,s2;

//the p process 
void* process_p(void* arg)
{
    printf("I am SC1\n"); 
    system("ls -l");
    sleep(1);
    sem_post(&s1);
    printf("I am SC2\n"); 
    system("ls -l");
    sleep(1);
    sem_post(&s1);
    printf("I am SC3\n"); 
    system("ls -l");
    sleep(1);
    sem_wait(&s2);
    
}

//the q process
void* process_q(void* arg)
{
    sem_wait(&s1);
    printf("I am SC4\n");
    system("ls -l");
    sleep(1);
    sem_post(&s2);
    sem_wait(&s1);
    printf("I am SC5\n");
    system("ls -l");
    sleep(1);
    
}

//main
int main()
{
    //arxikopoio toys s1,s2 me 0
    sem_init(&s1,0,0);
    sem_init(&s2,0,0);
    
    //sindew tis p,q diergasies with 2 threads
    pthread_t t1,t2;
    pthread_create(&t1,NULL,process_p,NULL); 
    pthread_create(&t2,NULL,process_q,NULL); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL);
    
    return 0;
}