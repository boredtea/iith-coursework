#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char const *argv[])
{
    int flag = 0; //checks if user wants to continue taking input

    //stores information for performing the calculation
    char operator = 'n';
    int number_1, number_2;

    int choice; //stores information about the user's choice


    while(flag == 0)
    {
        start:
        //taking operator input
        printf("Enter operator: ");
        fflush(stdin); //flushing buffer

        //keep getting a new char until you get a non-newline
        while((operator = getchar()) == '\n');
        

        //checking for invalid input
        if((operator != '+') && (operator != '-') && (operator != '*') && (operator != '/'))
        {
            printf("\nInvalid Operator: %c\n", operator);
            goto start;
        }

        //taking operand inputs
        printf("Enter the first number: ");
        scanf("%d", &number_1);
        printf("Enter the second number: ");
        scanf("%d", &number_2);

        //checking if input is within range
        if(abs(number_1*number_2) >= pow(10, 20))
        {
            printf("\nInput out of range.\n");
            goto start;
        }

        //performing the required operation using switch case
        switch (operator)
        {
            case '+': 
                printf("\nAddition\n");
                printf("%d\n\n", (number_1+number_2));     
                break;

            case '-': 
                printf("\nSubtraction\n");
                printf("%d\n\n", (number_1-number_2));     
                break;

            case '*': 
                printf("\nMultiplication\n");
                printf("%d\n\n", (number_1*number_2));     
                break;

            case '/': 
                printf("\nDivison\n");
                //checking if user is trying to divide by 0
                if(number_2 == 0)
                {
                    printf("Error.\n");     
                }
                else
                {
                    printf("%lf\n\n", (double)((double)number_1/(double)number_2));
                }
                break;
            
            default: 
                printf("\nInvalid Operator\n");
                goto start;
        }

        //checking if user would like to continue 
        menu:
        printf("Would you like to calculate something again?\n1. Yes\n2. No\nChoice: ");
        scanf("%d", &choice);
        printf("\n");
        fflush(stdin);
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
