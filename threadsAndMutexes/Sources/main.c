#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
#include <time.h>

pthread_t thread_id1;
pthread_t thread_id2;
pthread_mutex_t lock;
int counter; 


void* thread1(void* arg)
{ 
    for(;;)
    {
        pthread_mutex_lock(&lock); 
        printf("Hello world from thread 1\r\n");
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL; 
}
void* thread2(void* arg)
{ 
    for(;;)
    {
        pthread_mutex_lock(&lock); 
        printf("Hello world from thread 2\r\n");
        // sleep(2);
        pthread_mutex_unlock(&lock);
        sleep(1);    // change sleeptime to 2 seconds so you can clearly see what the mutex does
    }
    return NULL; 
}

int main(void)
{ 
    int error; 
  
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
    error = pthread_create(&thread_id1, NULL, &thread1, NULL); 
    if (error != 0) 
        printf("\nThread 1 can't be created : [%s]", strerror(error)); 
    error = pthread_create(&thread_id2, NULL, &thread2, NULL); 
    if (error != 0) 
        printf("\nThread 2 can't be created : [%s]", strerror(error)); 
  
    pthread_join(thread_id1, NULL); 
    pthread_join(thread_id2, NULL); 
    pthread_mutex_destroy(&lock); 
  
    return 0; 
} 