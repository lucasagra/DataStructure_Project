#include <stdio.h>
#include <stdlib.h>
#include "headers/compress.h"
#include "headers/decompress.h"

int main() {

    char *fileName = malloc(100);
    char buffer;

    printf("Open the file: ");
    scanf("%s%c", fileName, &buffer);

    printf("[1] Compress\n");
    printf("[2] Decompress\n");
    printf("[0] Exit\n");
    printf("Option >> ");
    scanf("%c", &buffer);

    switch (buffer)
    {
        case '1':
            compress(fileName);
            break;
        case '2':
            decompress(fileName);
            break;
        case '0':
            printf("System shutdown\n");
            break;
        default:
            printf("Invalid command\nShutting Down the system\n");
            break;
    }

    system("pause");
    free(fileName);
    return 0;
    
}