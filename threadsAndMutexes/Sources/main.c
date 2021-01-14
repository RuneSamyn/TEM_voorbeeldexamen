#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
  
pthread_t thread_id1; 
pthread_t thread_id2; 
int counter; 
  
void* thread1(void* arg) 
{ 
    printf("Hello world from thread 1\r\n");
    delay(1000);
    return NULL; 
} 
void* thread2(void* arg) 
{ 
    printf("Hello world from thread 2\r\n");
    delay(1000);
    return NULL; 
} 
  
int main(void) 
{ 
    int i = 0; 
    int error; 
  
    error = pthread_create(&thread_id1, NULL, &thread1, NULL); 
    if (error != 0) 
        printf("\nThread 1 can't be created : [%s]", strerror(error)); 
    error = pthread_create(&thread_id2, NULL, &thread2, NULL); 
    if (error != 0) 
        printf("\nThread 2 can't be created : [%s]", strerror(error)); 
  
    pthread_join(thread_id1, NULL); 
    pthread_join(thread_id2, NULL); 
  
    return 0; 
} 