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


char content[60030];
int flag_finish = 0;
void finish()
{
    flag_finish++;
}
void *listenFromIphone(void *args)
{

    printf("listeFromiPhone");
    int socket_client_iphone;
    int port = 2000;
    struct sockaddr_in server_address_iphone;
    int listen_sock;
    struct sockaddr_in client_address;
    int client_address_len = 0;
    memset(&server_address_iphone, 0, sizeof(server_address_iphone));
    server_address_iphone.sin_family = AF_INET;
    server_address_iphone.sin_port = htons(port);
    server_address_iphone.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("could not create listen socket\n");
    }

    if ((bind(listen_sock, (struct sockaddr *)&server_address_iphone,
              sizeof(server_address_iphone))) < 0)
    {
        printf("initCLientSocket could not bind socket\n");
    }

    int wait_size = 100000;
    if (listen(listen_sock, wait_size) < 0)
    {
        printf("could not open socket for listening\n");
    }
    while ((socket_client_iphone =
                accept(listen_sock, (struct sockaddr *)&client_address,
                       &client_address_len)) < 0)
    {

        // open a new socket to transmit data per connection
        if ((socket_client_iphone =
                 accept(listen_sock, (struct sockaddr *)&client_address,
                        &client_address_len)) < 0)
        {
            printf("could not open a socket to accept data\n");
        }
    }

    printf("client connected with ip address: %s\n",
           inet_ntoa(client_address.sin_addr));
    int n = 0;
    int lenn = 3;
    unsigned char bufferChunk[lenn];
    unsigned char chunk[2];
    unsigned int chunkID;
    while (((n = recv(socket_client_iphone, bufferChunk, lenn, 0)) > 0))
    {
        
        for (int i = 0; i < 2; i++)
        {
            chunk[i] = bufferChunk[i + 1];
        }
        
        memcpy(&chunkID, &chunk, 2);
        content[chunkID] = bufferChunk[0];
        printf("chunk  iphone\n");
        printf("%d", chunkID);
        printf("\n");
    }

    if (n == 0)
    {
        puts("Client disconnected iphone");
        close(socket_client_iphone);
        finish();
    }
    else if (n == -1)
    {
        perror("recv failed");
    }

    //printf('%d', count);

    close(socket_client_iphone);
    close(listen_sock);

    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    // pthread_t threads[NUM_THREADS];
    pthread_t threads;
    pthread_create(&threads, NULL, listenFromIphone, NULL);
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
    puts("file scritto iphone");
    exit(0);

    // printf("finish");
    // FILE *write_ptr;
    // write_ptr = fopen("foto.jpg", "wb");
    // fwrite(content, sizeof(content), 1, write_ptr);
    // fclose(write_ptr);
    // puts("file scritto");
}