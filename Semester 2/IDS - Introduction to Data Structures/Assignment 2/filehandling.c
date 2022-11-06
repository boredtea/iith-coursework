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

struct matrix
{
    Row *firstRow;
    int rows;
};
typedef struct matrix Matrix;

Row *createRow()
{
    Row *R = (Row *)malloc(sizeof(Row));
    R->columns = 0;
    Element *fakeStart = (Element *)malloc(sizeof(Element));
    fakeStart->next = NULL;
    R->start = fakeStart;
    R->next = NULL;
    return R;
}

void fillRow(Row *R, int Data, int position)
{
    Element *newElement = (Element *)malloc(sizeof(Element));
    newElement->info = Data;
    newElement->next = NULL;
    newElement->down = NULL;
    Element *currentElement = R->start;
    for (int i = 0; i < position - 1; i++)
    {
        currentElement = currentElement->next;
    }
    newElement->next = currentElement->next;
    currentElement->next = newElement;
    R->columns++;
}

void stitchRows(Matrix *M)
{

    Row *top = M->firstRow;
    Row *bottom = (M->firstRow)->next;
    Element *topElement;
    Element *bottomElement;

    while (bottom->next != NULL)
    {
        topElement = top->start;
        bottomElement = bottom->start;
        for (int i = 0; i < top->columns; i++)
        {
            //shifting both pointers to the next element
            topElement = topElement->next;
            bottomElement = bottomElement->next;

            topElement->down = bottomElement; //establishing the link between the upper and the lower row
        }
        top = bottom;
        bottom = bottom->next; 
    }
}

void readFromFile(char fileName[15], Matrix *M)
{
    Row *currentRow = M->firstRow;
    Row *newRow;

    FILE *filePointer;
    long fileSize;

    char *buffer;
    char extractedRow[50];
    //char fileName[15] = "Data.txt";

    size_t res;

    filePointer = fopen(fileName, "r+");

    //getting file size (used by buffer)
    fseek(filePointer, 0, SEEK_END);
    fileSize = ftell(filePointer);
    rewind(filePointer);

    buffer = (char *)malloc(sizeof(char) * fileSize);
    res = fread(buffer, 1, fileSize, filePointer);

    char *delimiter;                 //stores data from the file upto the custom delimiter
    delimiter = strtok(buffer, ";"); // Change the delimiter (“;”) on this line

    int length; //to store the length of the extracted row
    int element;
    int position;
    while (delimiter != NULL)
    {
        length = strlen(delimiter);

        //dealing with the extra character at the end of the last row
        if (!((delimiter[length - 1] >= '0') && (delimiter[length - 1] <= '9')))
            length--;

        for (int i = 0; i < length; i++)
        {
            extractedRow[i] = delimiter[i];
        }
        extractedRow[length] = ',';

        //extracting each element from the row
        char ch;
        position = 0;

        for (int i = 0; i <= length; i++)
        {
            ch = extractedRow[i];
            if ((ch >= '0') && (ch <= '9'))
            {
                element = (element * 10) + (extractedRow[i] - '0'); //converting the strings to an integer
            }
            else
            {
                fillRow(currentRow, element, ++position);
                element = 0;
            }
        }
        M->rows++;
        newRow = createRow();
        currentRow->next = newRow;
        currentRow = currentRow->next;

        delimiter = strtok(NULL, ";"); // Change the delimiter (“;”) on this line
    }

    fclose(filePointer);
    free(buffer);
}

//function to check if the given matrix is a square matrix
int squareCheck(Matrix *M)
{
    if((M->rows) == ((M->firstRow)->columns))
    return 0;
    else
    return -1;
}

void printMatrix(Matrix *M)
{
    Row *currentRow = M->firstRow; //pointer to travel through all the rows
    while (currentRow->next != NULL)
    {
        //printf("Current list: \n");
        Element *currentElement = currentRow->start;
        for (int i = 0; i < currentRow->columns; i++)
        {
            currentElement = currentElement->next;
            printf("%d  ", currentElement->info);
        }
        printf("\n\n");
        currentRow = currentRow->next;
    }
}



int main()
{
    char fileName[15];

    printf("Enter the name of the first input file (eg. Data.txt): ");
    scanf("%[^\n]%*c", fileName); 

    int squareFlag = 0; //flag to check whether a matrix is a square matrix or not

    //rows and matrix variables for the first input matrix
    Row *firstRowA = createRow();
    Matrix *matrixA = (Matrix *)malloc(sizeof(Matrix));
    matrixA->rows = 0;
    matrixA->firstRow = firstRowA;


    readFromFile(fileName, matrixA);
    stitchRows(matrixA);
    printMatrix(matrixA);

    squareFlag = squareCheck(matrixA);
    if(squareFlag == 0)
    printf("The given matrix is a square matrix.\n");
    else if(squareFlag == -1)
    printf("The given matrix is not a square matrix.\n");

    /*printf("Enter the name of the second input file (eg. Data.txt): ");
    scanf("%[^\n]%*c", fileName); 

    //rows and matrix variables for the second input matrix
    Row *firstRowB = createRow();
    Matrix *matrixB = (Matrix *)malloc(sizeof(Matrix));
    matrixB->rows = 0;
    matrixA->firstRow = firstRowB;

    readFromFile(fileName, matrixB);
    stitchRows(matrixB);
    printMatrix(matrixB);*/
    
    return 0;
}