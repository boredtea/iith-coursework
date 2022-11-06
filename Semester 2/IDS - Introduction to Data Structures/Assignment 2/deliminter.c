#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct element
{
    int info;
    struct element *next;
    struct element *down;
};
typedef struct element Element;

struct row
{
    Element *start;
    struct row *next;
    int columns;
};
typedef struct row Row;

Row* createRow()
{
    Row *R = (Row*)malloc(sizeof(Row));
    R->columns = 0;
    Element *fakeStart = (Element*)malloc(sizeof(Element));
    fakeStart->next = NULL;
    R->start = fakeStart;
    R->next = NULL;
    return R;
}

void readFromFile()
{
    FILE *filePointer;
    long fileSize;

    char *buffer;
    char extractedRow[50];
    char fileName[15] = "InputA.txt";

    size_t res;

    filePointer = fopen(fileName, "r+");

    //getting file size (used by buffer)
    fseek(filePointer, 0, SEEK_END);
    fileSize = ftell(filePointer);
    rewind(filePointer);

    buffer = (char *)malloc(sizeof(char) * fileSize);
    res = fread(buffer, 1, fileSize, filePointer);


    char *delimiter; //stores data from the file upto the custom delimiter
    delimiter = strtok(buffer, ";"); // Change the delimiter (“;”) on this line

    int length; //to store the length of the extracted row
    int element = 0;
    while (delimiter != NULL)
    {
        length = strlen(delimiter);

        //dealing with the extra character at the end of the last row
        if(!((delimiter[length - 1] >= '0') && (delimiter[length - 1] <= '9')))
            length--;

        for(int i = 0; i < length; i++)
        {
            extractedRow[i] = delimiter[i];
        }
        extractedRow[length] = ',';

        
        //extracting each element from the row
        char ch;
        for(int i = 0; i <= length; i++)
        {
            ch = extractedRow[i];
            if((ch >= '0') && (ch <= '9') )
            {
                element = (element * 10) + (extractedRow[i] - '0'); //converting the strings to an integer
            }
            else
            {
                printf("Extracted element: %d\n", element);
                element = 0;
            }
        }
        delimiter = strtok(NULL, ";"); // Change the delimiter (“;”) on this line
    }

    fclose(filePointer);
    free(buffer);

}

int main()
{
    Row *R = createRow();
    readFromFile();
    
    return 0;
}