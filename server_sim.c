#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <assert.h>
#include <pthread.h>
#include <net/if.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> /* for strncpy */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>    // for TCP_NODELAY
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/file.h>


int socket_client_mac;
int socket_client_iphone;
int SERVER_PORT = 3306;
struct sockaddr_in server_address;
int listen_sock;
struct sockaddr_in client_address;
int client_address_len = 0;
void initCLientSocket()
{

    while ((socket_client_mac =
                accept(listen_sock, (struct sockaddr *)&client_address,
                       &client_address_len)) < 0)
    {

        // open a new socket to transmit data per connection
        if ((socket_client_mac =
                 accept(listen_sock, (struct sockaddr *)&client_address,
                        &client_address_len)) < 0)
        {
            printf("could not open a socket to accept data\n");
            exit(0);
        }
    }
    printf("client connected with ip address: %s\n",
           inet_ntoa(client_address.sin_addr));
    
}

void sendBufferToClientMacChunk(unsigned char buffer[3])
{
    setsockopt(socket_client_mac, IPPROTO_TCP, TCP_NODELAY, 1, sizeof(int));
    send(socket_client_mac, buffer, 3, 0);
}

void serverIphone()
{
    printf("serverIphone");

    while (true)
    {
        // open a new socket to transmit data per connection
        int socket_client_iphone;
        if ((socket_client_iphone =
                 accept(listen_sock, (struct sockaddr *)&client_address,
                        &client_address_len)) < 0)
        {
            printf("could not open a socket to accept data\n");
            exit(0);
        }

        int n = 1;

        printf("client connected with ip address: %s\n",
               inet_ntoa(client_address.sin_addr));
        // keep running as long as the client keeps the connection open

        int lenn = 3;
        unsigned char bufferChunk[lenn];
    
        while (((n = recv(socket_client_iphone, bufferChunk, lenn, 0)) > 0))
        {
            printf("ricevo chunk \n");
            sendBufferToClientMacChunk(bufferChunk);
            sleep(1);
        }

        if (n == 0)
        {
            puts("Client disconnected");
            close(socket_client_mac);
            //exit(0);
            // printf("%s", content);
            // char str[12];
            // sprintf(str, "%d", count);
            // puts(str);
            // // w for write, b for binary

            // fwrite(content, sizeof(content), 1, write_ptr);
            // fclose(write_ptr);
            // puts("file scritto");
            // puts(count);
            //fflush(stdin);
        }
        else if (n == -1)
        {
            perror("recv failed");
        }

        //printf('%d', count);

        close(socket_client_iphone);
        close(listen_sock);
        exit(0);
    }
}

int main(int argc, char *argv[])
{

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("could not create listen socket\n");
        exit(0);
    }

    if ((bind(listen_sock, (struct sockaddr *)&server_address,
              sizeof(server_address))) < 0)
    {
        printf("initCLientSocket could not bind socket\n");
        exit(0);
    }

    int wait_size = 100000;
    if (listen(listen_sock, wait_size) < 0)
    {
        printf("could not open socket for listening\n");
        exit(0);
    }

    initCLientSocket();
    serverIphone();
    while (true)
    {
    }
}