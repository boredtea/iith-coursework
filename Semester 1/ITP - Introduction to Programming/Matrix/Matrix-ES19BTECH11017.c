#include <stdio.h>

//global 2-D array to deal with input matrices
int orders[2][2];

//variables to manage ordes of the two orders
int a1_x, a1_y, a2_x, a2_y;

//function to make sure order of the matrices are compatible for multiplication
void input_order()
{
    int flag = -1; //checks if column of first array is equal to row of second array
    int flag_one = 0; //checks for row or column matrices

    //keeps taking input until valid input is entered
    while(flag == -1)
    {
        for(int i = 0; i < 2; i++)
        {
            printf("Enter order for Array %d: ", i+1);
            for(int j = 0; j < 2; j++)
            {
                scanf("%d", &orders[i][j]);
                if(orders[i][j] == 1)
                {
                    flag_one = -1;
                }
            }
        }

        if(orders[0][1] == orders[1][0]) //column of first array is equal to row of second array
            flag = 0;
        else if((flag_one == -1) || (orders[0][1] != orders[1][0]))
        {
            printf("Error. Enter orders again.\n");
        }
    }
}

//function to take input of 2-D array
void input(int rows, int columns, int array[rows][columns])
{   
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            scanf("%d", &array[i][j]);
        }
    }
    printf("\n");
}


//function to find product of matrix A with matrix B
void multiplication(int A[a1_x][a1_y], int B[a2_x][a2_y], int C[a1_x][a2_y])
{
    for(int i = 0; i < a1_x; i++)
    {
        for(int j = 0; j < a2_y; j++)
        {
            C[i][j] = 0; //initialises each element of the multiplication matrix to 0
            for(int k = 0; k < a1_y; k++)
            {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }

    //printing product
    printf("Product:\n");
    for(int i = 0; i < a1_x; i++)
    {
        for(int j = 0; j < a2_y; j++)
        {
            printf("%d  ", C[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

//finds and stores cofactor matrix of an element
void cofactor(int size, int array[size][size], int temp[size][size], int a, int b)
{
    //variables used to fill up temp[][]
    int x = 0, y =  0;

    //copying elements of array into temp sans row a and column b
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if (i != a && j != b) //skipping elements of row a and column b
            {
                temp[x][y++] = array[i][j]; 
                //resetting and updating variables are reaching end of row
                if (y == size - 1) 
                { 
                    y = 0; 
                    x++; 
                } 
            } 
        }
    }
}

//function to calculate and return determinant of the matrix passed to it
float determinant(int size, int array[size][size])
{
    float det = 0;

    //base case
    if(size == 1)
        {
            det = array[0][0];
            return det;
        }

    int temp[size-1][size-1]; //used to store cofactor matrix
    
    int sign = 1; //keeps track of correct sign while calculating determinant

    //using the first row to calculate the determinant
    //but any other row can be used too
    for(int i = 0; i < size; i++)
    {
        cofactor(size, array, temp, 0, i);

        det = det + sign * array[0][i] * determinant(size - 1, temp);

        sign = -1 * sign;
    }
    return det;
}

//function to calculate and store the adjoint of an array
void adjoint(int size, int array[size][size], int adjoint[size][size])
{
    int temp[size - 1][size - 1]; //stores the cofactor of the passed array

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cofactor(size, array, temp, i, j);

            //inserting elements in the transposed matrix directly with correct sign
            if((i+j) % 2 == 0)
            adjoint[j][i] = determinant(size - 1, temp);
            else
            adjoint[j][i] = -determinant(size - 1, temp);
            
        }
    }
}

//function which calculates inverse of matrix using the above three functions
int inverse(int rows, int columns, int array[rows][columns])
{
    if(rows != columns) //check for rectangular matrices
    return -1;

    
    int size = rows;
    float det = determinant(size, array);

    if(det == 0) //check for singular matrices
    return -1;

    int adj[size][size]; //to store the adjoint
    adjoint(size, array, adj);
    
    float inv[size][size];
    printf("Inverse:\n");
    //dividing adjoint by determinant to get inverse matrix
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            inv[i][j] = adj[i][j] / (det);
            printf("%lf  ", inv[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int main(int argc, char const *argv[])
{
    //accepting the orders of the two input matrices
    input_order();

    //variables to manage ordes of the two orders
    a1_x = orders[0][0];
    a1_y = orders[0][1];
    a2_x = orders[1][0];
    a2_y = orders[1][1];

    //declaration of the required arrays
    int array_1[a1_x][a1_y], array_2[a2_x][a2_y];
    int multiplied[a1_x][a2_y];

    //taking input of the two arrays using the input() function
    printf("Enter elements for the first array row-wise: \n");
    input(a1_x, a1_y, array_1);
    printf("Enter elements for the second array row-wise: \n");
    input(a2_x, a2_y, array_2);

    multiplication(array_1, array_2, multiplied);
    
    int flag = 0; //to print error message in cases where inverse doesn't exist
    flag = inverse(a1_x, a2_y, multiplied);
    
    if(flag == -1)
     printf("Inverse of the matrix isn't possible.\n\n");

    return 0;
}

