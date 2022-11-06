#include <stdio.h>


int orders[2][2];

//variables to manage ordes of the two orders
int a1_x, a1_y, a2_x, a2_y;

int array_1[2][2], array_2[50][50], multiplied[50][50];
//int array_1[a1_x][a1_y], array_2[a2_x][a2_y];

//int multiplied[a1_x][a2_y];

void input_order()
{
    int flag = -1, flag_one = 0;

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

        if(orders[0][1] == orders[1][0])
            flag = 0;
        else if((flag_one == -1) || (orders[0][1] != orders[1][0]))
        {
            printf("Error. Enter orders again.\n");
        }
    }
}

//function to take input of an integer array with 10 elements
void input(int array[][2], int rows, int columns)
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


//finds and stores cofactor matrix of an element
void getCofactor(int A[][2], int temp[][2], int p, int q, int n) 
{ 
    int i = 0, j = 0; 
  
    // Looping for each element of the matrix 
    for (int row = 0; row < n; row++) 
    { 
        for (int col = 0; col < n; col++) 
        { 
            //  Copying into temporary matrix only those element 
            //  which are not in given row and column 
            if (row != p && col != q) 
            { 
                temp[i][j++] = A[row][col]; 
  
                // Row is filled, so increase row index and 
                // reset col index 
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 
  
/* Recursive function for finding determinant of matrix. 
   n is current dimension of A[][]. */
int determinant(int A[][2], int n) 
{ 
    int D = 0; // Initialize result 
  
    //  Base case : if matrix contains single element 
    if (n == 1) 
        return A[0][0]; 
  
    int temp[2][2]; // To store cofactors 
  
    int sign = 1;  // To store sign multiplier 
  
     // Iterate for each element of first row 
    for (int f = 0; f < n; f++) 
    { 
        // Getting Cofactor of A[0][f] 
        getCofactor(A, temp, 0, f, n); 
        D += sign * A[0][f] * determinant(temp, n - 1); 
  
        // terms are to be added with alternate sign 
        sign = -sign; 
    } 
  
    return D; 
} 

// Function to get adjoint of A[N][N] in adj[N][N]. 
void adjoint(int A[N][N],int adj[N][N]) 
{ 
    if (N == 1) 
    { 
        adj[0][0] = 1; 
        return; 
    } 
  
    // temp is used to store cofactors of A[][] 
    int sign = 1, temp[N][N]; 
  
    for (int i=0; i<N; i++) 
    { 
        for (int j=0; j<N; j++) 
        { 
            // Get cofactor of A[i][j] 
            getCofactor(A, temp, i, j, N); 
  
            // sign of adj[j][i] positive if sum of row 
            // and column indexes is even. 
            sign = ((i+j)%2==0)? 1: -1; 
  
            // Interchanging rows and columns to get the 
            // transpose of the cofactor matrix 
            adj[j][i] = (sign)*(determinant(temp, N-1)); 
        } 
    } 
} 
  
// Function to calculate and store inverse, returns false if 
// matrix is singular 
bool inverse(int A[N][N], float inverse[N][N]) 
{ 
    // Find determinant of A[][] 
    int det = determinant(A, N); 
    if (det == 0) 
    { 
        cout << "Singular matrix, can't find its inverse"; 
        return false; 
    } 
  
    // Find adjoint 
    int adj[N][N]; 
    adjoint(A, adj); 
  
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
    for (int i=0; i<N; i++) 
        for (int j=0; j<N; j++) 
            inverse[i][j] = adj[i][j]/float(det); 
  
    return true; 
} 

int main(int argc, char const *argv[])
{
    input_order();

    //variables to manage ordes of the two orders
    a1_x = orders[0][0];
    a1_y = orders[0][1];
    a2_x = orders[1][0];
    a2_y = orders[1][1];

    //int array_1[50][50], array_2[50][50], multiplied[50][50];
    //int array_1[a1_x][a1_y], array_2[a2_x][a2_y];

    printf("Enter elements for array row-wise: \n");
    input(array_1, a1_x, a1_y);
    //printf("Enter elements for the second array row-wise: \n");
    //input(array_2, a2_x, a2_y);

    //multiplication(array_1, array_2, multiplied);
    
    int det = determinant(array_1, a1_x);
    printf("Determinant: %d\n\n", det);

    return 0;
}
