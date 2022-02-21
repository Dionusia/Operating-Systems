#include <stdio.h> 
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t x, wsem;
int data = 0, readcount = 0;

void* reader(void* arg)
{
    while(1){
    sem_wait(&x);
    readcount++;
    if (readcount == 1)
    printf("Data read by the reader is %d\n",data);
    sleep(1);
    readcount--;
    if (readcount == 0)
        sem_post(&wsem);
}
}
void* writer(void* arg)
{
    
    while(1){
    sem_wait(&wsem);
    data++;
    printf("Data writen by the writer is %d\n",data);    
    sleep(1);
    sem_post(&x);
    }
}
int main()
{
    
    pthread_t rtid, wtid;
    sem_init(&x, 0, 0);
    sem_init(&wsem, 0, 1);
    
        pthread_create(&wtid, NULL, writer, 1);
        pthread_create(&rtid, NULL, reader, 1);
    
   
        pthread_join(wtid, NULL);
        pthread_join(rtid, NULL);
    
    return 0;
}
