#include <stdio.h>

//function to compute a+b
double add(int a, int b)
{
    if(a <= 0 || b <= 0)
        return -1;

    double result = a + b;
    return result;
}

//function to compute a-b
double subtract(int a, int b)
{
    if(a <= 0 || b <= 0)
        return -1;

    double result = a - b;
    return result;
}

//function to compute a*b
double multiply(int a, int b)
{
    if(a <= 0 || b <= 0)
        return -1;

    double result = 0;

    //code to make program more efficient
    int larger, smaller;
    larger = (a > b) ? a : b;
    smaller = (a < b) ? a : b;
    for(int i = 1; i <= smaller; i++)
    {
        result = result + larger;
    }

    return result;
}

//function to compute the floor of a/b
double divide(int a, int b)
{
    if(a <= 0 || b <= 0)
        return -1;

    double result = 0;

    double sum = 0;
    while(sum <= a)
    {
        result++;
        sum = sum + b;
    }
    --result;

    return result;
}

//function to compute a%b
double modulus(int a, int b)
{
    if(a <= 0 || b <= 0)
        return -1;

    double result;

    double sum = 0;
    while(sum <= a)
    {
        sum = sum + b;
    }
    result = a - (sum - b);

    return result;
}

//function to compute a*a
double square(int a)
{
    double result = multiply(a, a);

    return result;
}

//function to compute square root of a
double root(int a)
{
    if(a <= 0)
        return -1;

    double result = 1;

    double product = 1;

    while(product <= a)
    {
        product = square(result);
        result++;
    }
    result = result - 2;

    return result;
}

//function to compute log a to the base b
double logarithm(int a)
{
    if(a <= 0)
        return -1;
    
    double result = 0;

    double product = 1;

    while(product < a)
    {
        product = multiply(product, 2);
        result++;
    }

    return result;
}


int main(int argc, char const *argv[])
{
    //stores numbers for performing the calculation
    int number_1, number_2;

    int choice = 0; //stores information about the user's choice


    while(choice != 9)
    {
        printf("***MENU***\n");
        printf("Enter the number corresponding to the operation you want to perform\n");
        printf("1. Add\n2. Multiply\n3. Divide\n4. Subtract\n5. Modulus\n6. Square\n7. Square Root\n8. Logarithm (base: 2)\n9. Exit\n");   
        printf("Choice: ");

        scanf("%d", &choice);

        //taking required number of inputs according to the selected operation
        switch(choice)
        {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                printf("\nEnter the first number: ");
                scanf("%d", &number_1);
                printf("Enter the second number: ");
                scanf("%d", &number_2);
                break;
            case 6:
            case 7:
            case 8:
                printf("\nEnter the number: ");
                scanf("%d", &number_1);
                break;
        }

        //performing the required operation using switch case
        switch (choice)
        {
            case 1: 
                if(add(number_1, number_2) == -1)
                    printf("Invalid input.\n\n");
                else
                    printf("The result is: %lf\n\n", add(number_1, number_2));
                break;

            case 2:
                if(multiply(number_1, number_2) == -1)
                    printf("Invalid input.\n\n");
                else
                    printf("The result is: %lf\n\n", multiply(number_1, number_2));
                break;

            case 3:
                if(divide(number_1, number_2) == -1)
                    printf("Invalid input.\n\n");
                else
                    printf("The result is: %lf\n\n", divide(number_1, number_2));
                break;

            case 4:
                if(subtract(number_1, number_2) == -1)
                    printf("Invalid input.\n\n");
                else
                    printf("The result is: %lf\n\n", subtract(number_1, number_2));
                break;
            
            case 5:
                if(modulus(number_1, number_2) == -1)
                    printf("Invalid input.\n\n");
                else
                    printf("The result is: %lf\n\n", modulus(number_1, number_2));
                break;
            
            case 6:
                if(square(number_1) == -1)
                    printf("Invalid input.\n\n");
                else
                    printf("The result is: %lf\n\n", square(number_1));
                break;
            
            case 7:
                if(root(number_1) == -1)
                    printf("Invalid input.\n\n");
                else
                    printf("The result is: %lf\n\n", root(number_1));
                break;

            case 8:
                if(logarithm(number_1) == -1)
                    printf("Invalid input.\n\n");
                else
                    printf("The result is: %lf\n\n", logarithm(number_1));
                break;

            case 9:
                printf("\nThank you!!!\n");
                break;
            
            default: 
                printf("\nInvalid input.\n\n");
        }
    }
    return 0;
}
