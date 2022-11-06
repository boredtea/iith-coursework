#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    FILE *filePointer;
    filePointer = fopen("input.txt", "r");

    char data[10];
    fseek(filePointer, 0, SEEK_SET);

    fscanf(filePointer, "%s", data);
    printf("%s\n", data);
    int N = atoi(data);


    printf("%d\n", N);
    int num;

    for(int i = 1; i <= N; i++)
    {
        fscanf(filePointer, "%s", data);
        num = atoi(data);
        printf("%d ", num);
    }

    printf("\n");

}