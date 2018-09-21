#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2
char content[60030];
int flag_finish = 0;

void finish()
{
    flag_finish++;
}

void *listenFromServer(void *args)
{
    const char *server_name = "18.191.173.32";
    const int server_port = 3306;

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;

    // creates binary representation of server name
    // and stores it as sin_addr
    // http://beej.us/guide/bgnet/output/html/multipage/inet_ntopman.html
    inet_pton(AF_INET, server_name, &server_address.sin_addr);

    // htons: port in network order format
    server_address.sin_port = htons(server_port);

    // open a stream socket
    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("could not create socket\n");
    }

    // TCP is connection oriented, a reliable connection
    // **must** be established before any data is exchanged
    if (connect(sock, (struct sockaddr *)&server_address,
                sizeof(server_address)) < 0)
    {
        printf("could not connect to server\n");
    }

    // receive

    int n = 0;
    int len = 3;
    unsigned char bufferChunk[len];
    unsigned char chunk[2];
    unsigned int chunkID;
    int i = 0;
    while (((n = recv(sock, bufferChunk, len, 0)) > 0))
    {

        for (i = 0; i < 2; i++)
        {
            chunk[i] = bufferChunk[i + 1];
        }
        printf("faccio memcpy");
        memcpy(&chunkID, &chunk, 2);
        printf("memcpy finito");
        printf("salvo carattere");
        content[chunkID] = bufferChunk[0];
        printf("finito salvataggio carattere");
        // printf("chunk server\n");
        // printf("%d", chunkID);
        // printf("\n");
    }

    if (n == 0)
    {
        puts("Client disconnected server");
        printf("%s", content);
        finish();

    }
    else if (n == -1)
    {
        perror("recv failed");
    }
    close(sock);
    pthread_exit(NULL);
}



int main(int argc, char *argv[])
{
    // pthread_t threads[NUM_THREADS];
    pthread_t threads;
    pthread_create(&threads, NULL, listenFromServer, NULL);
    // for (int i = 0; i < NUM_THREADS; i++)
    // {
    //     if (i == 0)
    //         pthread_create(&threads[0], NULL, listenFromServer, NULL);
    //     else
    //         pthread_create(&threads[1], NULL, listenFromIphone, NULL);
            
    // }
    // for (int i = 0; i < 2; i++)
    //    pthread_join(threads[i], NULL);
    pthread_join(threads, NULL);
    while (flag_finish < 1)
    {
    }
    puts("file scritto server");
    exit(0);

    // printf("finish");
    // FILE *write_ptr;
    // write_ptr = fopen("foto.jpg", "wb");
    // fwrite(content, sizeof(content), 1, write_ptr);
    // fclose(write_ptr);
    // puts("file scritto");
}