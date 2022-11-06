#include <stdio.h>

//function to compute factorial
long long int factorial(int x)
{
    long long int factorial = 1;

    for(int i = 2; i <= x; i++)
        factorial = i * factorial;

    return factorial;
}

//function to compute combination
long long int combination(int x, int y)
{
    long long int combination;

    if(x >= y)
    {
        //calling the factorial() function to compute combination
        combination = factorial(x) / (factorial(y) * factorial(x - y));
        return combination;
    }
    else
    {
        return -1;
    }
}

int main(int argc, char const *argv[])
{

    int flag = 0; //checks if user wants to continue taking input

    //stores information for performing the calculation
    int number_1, number_2;

    long long int comb; //stores the answer or return status of combination()

    int choice; //stores information about the user's choice

    //while loop to keep taking inputs until stated otherwise
    while(flag == 0)
    {
        //taking inputs
        printf("Enter the first number (x): ");
        scanf("%d", &number_1);
        printf("Enter the second number (y): ");
        scanf("%d", &number_2);

        comb = combination(number_1, number_2); //calling the combination() function

        //print output
        if(comb == -1)
            printf("\nIncorrect input!\n\n");
        else
        {
            printf("Answer: %lld\n\n", comb);
        }
        
        //checking if user would like to continue
        menu:
        printf("Would you like to calculate something again?\n1. Yes\n2. No\nChoice: ");
        scanf("%d", &choice);
        printf("\n");
        if(choice == 1)
        {
            flag = 0;
        }
        else if(choice == 2)
        {
            printf("Thank you!\n");
            flag = -1;
        }
        else
        {
            printf("Invalid Input\n\n");
            goto menu;
        }
    }
    
    return 0;
}
