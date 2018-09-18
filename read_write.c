#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

    FILE *fp;

    fp = fopen("bull_no_geometrie.jpg", "rb"); // r for read, b for binary
    fseek(fp, 0L, SEEK_END);
    long sz = ftell(fp);
    unsigned char buffer[(int)sz];
    fseek(fp, 0L, SEEK_SET);
    fread(buffer, sizeof(buffer), 1, fp);
    fclose(fp);
    FILE *write_ptr;

    write_ptr = fopen("nuova_foto.jpg", "wb"); // w for write, b for binary

    fwrite(buffer, sizeof(buffer), 1, write_ptr); // write 10 bytes from our buffer
    fclose(write_ptr);
}
