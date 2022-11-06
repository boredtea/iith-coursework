#include <stdio.h>

int main(int argc, char const *argv[])
{
    int N = -1; //checks how many times user wants to gove input
    char operation = 'n'; //stores information about the type of operation
    int I; //initial balance
    int amount; //amount the user would like to add or withdraw from their bank account

    //asking user how many times they'd like to input data
    
    //taking input continuously until valid value of N is entered
    while(N < 0)
    {
        printf("Enter the number of operations you would like to perform: ");
        scanf("%d", &N);

        if(N < 0)
        printf("\nPlease enter a valid value for N.\n\n");
    }


    if(N >= 0)
    {
        //taking note of current bank balance
        printf("Enter current balance: ");
        scanf("%d", &I);

        //taking input N times
        for(int i = 1; i  <= N; i++)
        {
            printf("Enter operation you would like to perform (w, a or p): ");
            //keep getting a new char until you get a non-newline
            while((operation = getchar()) == '\n');

            //taking amount input only when necessary
            switch(operation)
            {
                case 'w':
                case 'a': 
                    printf("Enter amount: ");
                    scanf("%d", &amount);
                        break;
                case 'p':
                    break;
                default: 
                    printf("\nInvalid Operator: %c\n", operation);
            }

            //performing the required operation using switch case
            switch (operation)
            {
                case 'w': 
                    if(amount <= I) //checking if current balance is enough to complete withdrawal request
                    {
                        printf("\nWithdrawAmount\n");
                        I = I - amount;
                        printf("Success!\n\n");
                    }
                    else
                    {
                        printf("\nError\n\n");
                    }
                    break;

                case 'a': 
                    printf("\nAddAmount\n");
                    I = I + amount;
                    printf("Success!\n\n");     
                    break;

                case 'p': 
                    printf("\nGetBalance\n");
                    printf("%d\n\n", I);     
                    break;
            }
        }
    }
    else
    {
        printf("\nPlease enter a valid value for N.\n\n");
    }
    
    return 0;
}
