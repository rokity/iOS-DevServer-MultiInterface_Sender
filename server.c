#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *serverThreadIphone(void *vargp) 
{ 
    sleep(1); 
    printf("Printing GeeksQuiz from Thread \n"); 
    return NULL; 
} 

int main(int argc, char *argv[]) {
    pthread_t serverThreadIphoneId; 
    pthread_create(&serverThreadIphoneId, NULL, serverThreadIphone, NULL); 
    
    while(true)
    {

    }
}