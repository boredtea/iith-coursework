#include <stdio.h>

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

int Sum;
int primeSum(long int n)
{
    if (n % 10 == 2)
    {
        n = n / 10;
        Sum = 2 + primeSum(n);
    }
    else if (n % 10 == 3)
    {
        n = n / 10;
        Sum = 3 + primeSum(n);
    }
    else if (n % 10 == 5)
    {
        n = n / 10;
        Sum = 5 + primeSum(n);
    }
    else if (n % 10 == 7)
    {
        n = n / 10;
        Sum = 7 + primeSum(n);
    }
    else if(n != 0)
    {
        n = n / 10;
        Sum = primeSum(n);
    }
    else
        return Sum;
}

void main(int argc, char const *argv[])
{
    long int Number;
    printf("INPUT:-");
    scanf("%ld", &Number);
    if (Number > 0)
    {
        if (digit(Number) == 10)
        {
            int sumPrime = primeSum(Number);
        }
        else
        {
            printf("INCORRECT INPUT!! Please enter again\n");
        }
    }
    else
    {
        printf("INCORRECT INPUT!! Please enter again\n");
    }
    printf("%d\n", digit(Number));
}