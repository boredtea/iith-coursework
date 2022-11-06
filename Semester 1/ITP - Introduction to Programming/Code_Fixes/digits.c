#include <stdio.h>

int count = 0;
int sum = 0;

//function to compute a+b
int digit(long int k)
{
    int i = 0; // Value of i initializes to zero.
    if (k != 0)
    {
        i++; //increments the value when n not equal to zero
        return i + digit(k / 10);
    }
    else
    {
        return 0;
    }
}

int main(int argc, char const *argv[])
{
    long number;
    int count = 0;

    printf("Enter number: ");
    scanf("%ld", &number);

    count = digit(number);

    printf("%d\n", count);

    return 0;
}