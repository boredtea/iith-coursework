#include <stdio.h>

int main(int argc, char const *argv[])
{
    int flag = 0; //checks if user wants to continue taking input
    int N; //stores information for performing the calculation
    long product; // stores the product
    int current; //variable used to iterate through all even natural numbers in the while loop
    int choice; //stores information about the user's choice


    //while loop to keep taking input until stated otherwise
    while(flag == 0)
    {
        //taking input
        printf("Enter N: ");
        scanf("%d", &N);
        
        if((N <= 0) || (N > 30)) //checking for invalid and out of range input
        {
            printf("Error!\n\n"); //printing error message
        }
        else if(N == 1)
        {

        }
        else
        {
            //initialising variables
            product = 1;
            current = 2; 

            //performing the required operation using while
            while(current <= N)
            {
                printf("%d ", current); //printing current even number
                product = product*current; //multiplying the current even number with product (type promotion occurs here)
                current = current+2; //incrementing current number to the next even number
            }
            
            printf("\n%ld\n\n", product); //printing the product
        }

        //checking if user would like to continue 
        menu:
        printf("Would you like to calculate product again?\n1. Yes\n2. No\nChoice: ");
        scanf("%d", &choice);
        printf("\n");
        if(choice == 1)
        {
            flag = 0;
        }
        else if(choice == 2)
        {
            printf("\nThank you!\n");
            flag = -1;
        }
        else
        {
            printf("\nInvalid Input\n");
            goto menu;
        }
    }
    return 0;
}
