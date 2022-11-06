#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure to create a node element
struct element
{
    int info;
    struct element *next;
    struct element *down;
};
typedef struct element Element;

//structure to create a row
struct row
{
    Element *start;
    struct row *next;
    int columns;
};
typedef struct row Row;

//structure to point to the first row of a matrix
struct matrix
{
    Row *firstRow;
    int rows;
};
typedef struct matrix Matrix;


//function to allocate memory and create an empty row
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

//function to fill up a row with values at the specified position
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

//function to establish links between the corresponding elements of two adjacent matrices
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

//function to read the matrix from a file and store it in a dynamic matrix
void readFromFile(char fileName[15], Matrix *M)
{
    //pointers to help fill up matrix M
    Row *currentRow = M->firstRow;
    Row *newRow;

    //Declaring the file pointer
    FILE *filePointer;
    long fileSize;

    char *buffer;
    char extractedRow[50];

    size_t res;

    //opening the file in read mode
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
    int sign = 1;
    int position;
    //loop to read individual numbers from the current extracted row
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
            if (((ch >= '0') && (ch <= '9')) || (ch == '-'))
            {
                if (ch == '-') //for negative numbers
                    sign = -1;
                else
                    element = (element * 10) + (extractedRow[i] - '0'); //converting the strings to an integer
            }
            else
            {
                element = element * sign;
                fillRow(currentRow, element, ++position);
                element = 0;
                sign = 1;
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
    if ((M->rows) == ((M->firstRow)->columns))
        return 0;
    else
        return -1;
}

//function to check if the given matrix is a symmetric matrix
void checkSymmetry(Matrix *M, int squareFlag)
{
    int flag = 0;
    if (squareFlag == 0)
    {
        Row *currentRow = M->firstRow;
        Element *columnHead = currentRow->start->next; //makeshift start pointer for each column
        //making the pointers point to the first element in the matrix
        Element *currentRowElement = currentRow->start->next; //pointer to travel through a row
        Element *currentColumnElement = columnHead;           //pointer to travel through a column

        for (int i = 1; i <= M->rows; i++)
        {
            while (currentRowElement->next != NULL)
            {
                if (currentRowElement->info == currentColumnElement->info)
                {

                    //traversing to the next element in the respective row or column only if the condition is satisfied
                    currentRowElement = currentRowElement->next;
                    currentColumnElement = currentColumnElement->down;
                }
                else
                {
                    flag = -1;
                    break;
                }
            }
            if (flag == -1)
                break;
            else
            {
                currentRow = currentRow->next;
                columnHead = columnHead->next;
                currentRowElement = currentRow->start->next;
                currentColumnElement = columnHead;
            }
        }
        if (flag == 0)
            printf("Given matrix is a symmetric matrix.\n\n");
        else if (flag == -1)
            printf("Given matrix is not a symmetric matrix.\n\n");
    }
    else
    {
        printf("Given matrix is not a square matrix and thus can't be checked for symmetry.\n\n");
    }
}

//function to check if two matrices can be multiplied together
int checkCompatibility(Matrix *A, Matrix *B)
{
    int compatibility = 0; //flag to check if the given matrices can be multiplied
    if (A->firstRow->columns == B->rows)
        compatibility = 1;
    else
        compatibility = -1;

    return compatibility;
}

//function to multiply two matrices together
void multiply(Matrix *A, Matrix *B, Matrix *Product)
{
    Row *currentRow = A->firstRow;
    Element *columnHead = B->firstRow->start->next; //makeshift start pointer for each column
    //making the pointers point to the first element in the matrix
    Element *currentRowElement = currentRow->start->next; //pointer to travel through a row
    Element *currentColumnElement = columnHead;           //pointer to travel through a column

    //Row pointers to help store the multiplied product in the product matrix
    Row *currentProductRow = Product->firstRow;
    Row *newProductRow;

    int product = 0;
    for (int i = 1; i <= A->rows; i++)
    {
        for (int j = 1; j <= B->firstRow->columns; j++)
        {
            for(int k = 1; k <= B->rows; k++)
            {
                printf("Column head: %d\n", columnHead->info);

                product = product + (currentRowElement->info * currentColumnElement->info);

                //traversing to the next element in the respective row or column only if the condition is satisfied
                currentRowElement = currentRowElement->next;
                currentColumnElement = currentColumnElement->down;
            }
            //multiplying the current row with the next column
            printf("i: %d j: %d product: %d\n", i, j, product);
            fillRow(currentProductRow, product, j);
            currentRowElement = currentRow->start;
            columnHead = columnHead->next;
            currentColumnElement = columnHead;
            product = 0;
        }
        currentRow = currentRow->next;
        columnHead = B->firstRow->start->next;
        currentRowElement = currentRow->start->next;
        currentColumnElement = columnHead;

        //shifting pointers to write into the next row in the product matrix
        Product->rows++;
        newProductRow = createRow();
        currentProductRow->next = newProductRow;
        currentProductRow = currentProductRow->next;
        product = 0;
    }
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

void writeToFile(Matrix *M)
{
    //pointer to travel through matrix and print to file
    Row *currentRow = M->firstRow;

    //Declaring the file pointer
    FILE *filePointer;

    // Get the data to be written in file

    // Open the existing file GfgTest.c using fopen()
    // in write mode using "w" attribute
    filePointer = fopen("Output.txt", "w");

    if (filePointer == NULL)
    {
        printf("Output.txt file failed to open.");
    }
    else
    {
        //writing into the file
        while (currentRow->next != NULL)
        {
            //printf("Current list: \n");
            Element *currentElement = currentRow->start;
            for (int i = 0; i < currentRow->columns; i++)
            {
                currentElement = currentElement->next;
                fprintf(filePointer, "%d", currentElement->info);
                fputs("    ", filePointer);
            }
            fputs("\n", filePointer);
            currentRow = currentRow->next;
        }

        // Closing the file using fclose()
        fclose(filePointer);
    }
}

int main()
{
    //rows and matrix variables for the first input matrix
    Row *firstRowA = createRow();
    Matrix *matrixA = (Matrix *)malloc(sizeof(Matrix));
    matrixA->rows = 0;
    matrixA->firstRow = firstRowA;

    //rows and matrix variables for the second input matrix
    Row *firstRowB = createRow();
    Matrix *matrixB = (Matrix *)malloc(sizeof(Matrix));
    matrixB->rows = 0;
    matrixB->firstRow = firstRowB;


    int squareFlag = 0; //flag to check whether a matrix is a square matrix or not
    
    //reading from both input files and storing data in a linked list
    char fileName[15];

    printf("Enter the name of the first input file (eg: Data.txt): ");
    scanf("%[^\n]%*c", fileName);
    readFromFile(fileName, matrixA);
    stitchRows(matrixA); //connecting rows together

    printf("Enter the name of the second input file (eg: Data.txt): ");
    scanf("%[^\n]%*c", fileName);
    readFromFile(fileName, matrixB);
    stitchRows(matrixB); //connecting rows together



    //PRINTING AND PERFORMING CHECKS ON THE FIRST MATRIX
    printf("First matrix: \n");
    printMatrix(matrixA); //displaying the first matrix

    //checking if the first matrix is a square matrix
    squareFlag = squareCheck(matrixA);
    if (squareFlag == 0)
        printf("The first matrix is a square matrix.\n");
    else if (squareFlag == -1)
        printf("The first matrix is not a square matrix.\n");

    //checking if the first matrix is symmetric
    checkSymmetry(matrixA, squareFlag);



    //PRINTING AND PERFORMING CHECKS ON THE SECOND MATRIX
    printf("Second matrix: \n");
    printMatrix(matrixB); //displaying the second matrix

    //checking if the second matrix is a square matrix
    squareFlag = squareCheck(matrixB);
    if (squareFlag == 0)
        printf("The second matrix is a square matrix.\n");
    else if (squareFlag == -1)
        printf("The second matrix is not a square matrix.\n");

    //checking if the second matrix is symmetric
    checkSymmetry(matrixB, squareFlag);


    //MULTIPLYING THE TWO MATRICES
    int choice;        //to check if the user wants to multiply the matrices
    int compatibility; //flag to check if two matrices can be multiplied in the given order
    printf("Would you like to multiply the two input matrices?\n1. Yes\n2. No\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Chose order of multiplication:\n");
        printf("1. First Matrix * Second Matrix\n2. Second Matrix * First Matrix\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1)
            compatibility = checkCompatibility(matrixA, matrixB);
        else if (choice == 2)
            compatibility = checkCompatibility(matrixB, matrixA);

        if (compatibility == 1)
        {
            //rows and matrix variables for the product matrix
            Row *firstProductRow = createRow();
            Matrix *product = (Matrix *)malloc(sizeof(Matrix));
            product->rows = 0;
            product->firstRow = firstProductRow;

            if (choice == 1)
                multiply(matrixA, matrixB, product);
            else
                multiply(matrixB, matrixA, product);

            writeToFile(product);
            printf("The product matrix has been stored in the file \"Output.txt\"\n\n");
        }
        else
        {
            printf("The given matrices cannot be multiplied together.\n\n");
        }
    }
    else
    {
        printf("Thank you!\n\n");
    }
    

    return 0;
}