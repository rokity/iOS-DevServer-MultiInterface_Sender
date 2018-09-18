#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int socket_client_mac;
void initCLientSocket()
{
    int SERVER_PORT = 2001;
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    int listen_sock;
    if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("could not create listen socket\n");
    }
    if ((bind(listen_sock, (struct sockaddr *)&server_address,
              sizeof(server_address))) < 0)
    {
        printf("could not bind socket\n");
    }
    int wait_size = 1000;
    if (listen(listen_sock, wait_size) < 0)
    {
        printf("could not open socket for listening\n");
    }
    struct sockaddr_in client_address;
    int client_address_len = 0;
    while (true)
    {
        // open a new socket to transmit data per connection
        if ((socket_client_mac =
                 accept(listen_sock, (struct sockaddr *)&client_address,
                        &client_address_len)) < 0)
        {
            printf("could not open a socket to accept data\n");
        }

        printf("client connected with ip address: %s\n",
               inet_ntoa(client_address.sin_addr));
    }
}

void sendBufferToClientMac(char buffer[])
{
    size_t len = strlen(buffer);
    send(socket_client_mac, buffer, len, 0);
}

void serverIphone()
{
    int SERVER_PORT = 2000;
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    int listen_sock;
    if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("could not create listen socket\n");
    }
    if ((bind(listen_sock, (struct sockaddr *)&server_address,
              sizeof(server_address))) < 0)
    {
        printf("could not bind socket\n");
    }
    int wait_size = 1000;
    if (listen(listen_sock, wait_size) < 0)
    {
        printf("could not open socket for listening\n");
    }
    struct sockaddr_in client_address;
    int client_address_len = 0;
    while (true)
    {
        // open a new socket to transmit data per connection
        int sock;
        if ((sock =
                 accept(listen_sock, (struct sockaddr *)&client_address,
                        &client_address_len)) < 0)
        {
            printf("could not open a socket to accept data\n");
        }

        int n = 0;
        int len = 0, maxlen = 1;
        char buffer[maxlen];

        printf("client connected with ip address: %s\n",
               inet_ntoa(client_address.sin_addr));
        int count = 0;
        FILE *write_ptr;

        write_ptr = fopen("foto.jpg", "wb");
        char content[60030];
        // keep running as long as the client keeps the connection open
        while ((n = recv(sock, buffer, maxlen, 0)))
        {
            content[count]= buffer[0];
            printf("%s", buffer);
            printf("\n");
            count++;
            //printf("received: '%s'\n", buffer);
        }
        if (n == 0)
        {
            puts("Client disconnected");
            printf("%s", content);
            char str[12];
            sprintf(str, "%d", count);
            puts(str);
            // w for write, b for binary

            fwrite(content, sizeof(content), 1, write_ptr);
            fclose(write_ptr);
            puts("file scritto");
            // puts(count);
            //fflush(stdin);
        }
        else if (n == -1)
        {
            perror("recv failed");
        }

        //printf('%d', count);

        //close(sock);
    }
    //close(listen_sock);
}

int main(int argc, char *argv[])
{
    serverIphone();
    initCLientSocket();
    while (true)
    {
    }
}