#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
        int len = 0, maxlen = 100;
        char buffer[maxlen];
        char *pbuffer = buffer;

        printf("client connected with ip address: %s\n",
               inet_ntoa(client_address.sin_addr));

        // keep running as long as the client keeps the connection open
        while ((n = recv(sock, pbuffer, maxlen, 0)) > 0)
        {
            pbuffer += n;
            maxlen -= n;
            len += n;

            printf("received: '%s'\n", buffer);

            // echo received content back
            send(sock, buffer, len, 0);
        }

        close(sock);
    }
    close(listen_sock);
}

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




int main(int argc, char *argv[])
{
    serverIphone();
    initCLientSocket();
    while (true)
    {
    }
}