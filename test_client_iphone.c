#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <yajl/yajl_parse.h>
#include <yajl/yajl_gen.h>

struct rec
{
    int x, y, z;
};

int main(int argc, char *argv[])
{

    const char *server_name = "localhost";
    const int server_port = 2000;

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
        return 1;
    }

    // TCP is connection oriented, a reliable connection
    // **must** be established before any data is exchanged
    if (connect(sock, (struct sockaddr *)&server_address,
                sizeof(server_address)) < 0)
    {
        printf("could not connect to server\n");
        return 1;
    }

    // send

    FILE *f = fopen("bull_no_geometrie.jpg", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET); //same as rewind(f);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);

    char buff[3];
    for(int i =0;i<fsize;i=i+3)
    {
        strncpy(buff, &string[i], 3);

        send(sock, data_to_send, strlen(data_to_send), 0);
    }
    // data that will be sent to the server
    

    // close the socket
    close(sock);
    return 0;
}