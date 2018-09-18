#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void listenFromServer()
{
    const char *server_name = "127.0.0.1";
    const int server_port = 2001;

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
    int count = 0, maxlen = 1;
    char buffer[maxlen];
    char content[60030];

    FILE *write_ptr;
    write_ptr = fopen("foto.jpg", "wb");
    
    // will remain open until the server terminates the connection
    while ((n = recv(sock, buffer, maxlen, 0)) > 0)
    {
        content[count]= buffer[0];
        count++;
        printf("received: '%s'\n", buffer);
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

}

int main(int argc, char *argv[])
{
    listenFromServer();
    while (true)
    {
    }
}