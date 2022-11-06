#include <stdio.h>

//global variables used by the recursive functions
int count = 0;
int sum = 0;

//recursive function that checks if a number is 10 digits long
int validity_check(long n)
{    
    if(n < 0) //negative integers are invalid
        return -1;
    else if(n != 0) //counting number of digits
    {
        count++;
        n = n / 10;
        return validity_check(n);
    }
    else if(n == 0) //stops counting when the number has become 0
        return count;

}

//recursive function that calculates sum of prime digits in number
int prime_sum(long n)
{
    int digit;
    digit = n % 10; //extracts digit in unit's place
    n = n / 10; //removes digit in unit's place

    //if the digit is prime, it gets added to the sum
    if(digit == 2 || digit == 3 || digit == 5 || digit == 7)
    {
        sum = digit + prime_sum(n);
    }
    else if(n != 0)
        prime_sum(n);
    else //returns final sum when n has become 0
        return sum;
    
}


int main(int argc, char const *argv[])
{
    long number; //used for storing the input

    int flag = -1; //stores information about the validity of input

    int length;
    int result;

    //loop to keep taking input until valid input is entered
    while(flag == -1)
    {
        printf("Enter number: ");
        scanf("%ld", &number);

        count = 0;
        length = validity_check(number);

        if(length == 10) //calls the prime_sum() function only when input is valid
        {
            result = 0;
            result = prime_sum(number);
            printf("Sum of primes: %d\n\n", result);
            flag = 1;
        }
        else
        {
            printf("Invalid input. Plese re-enter.\n");
            flag = -1;
        }
    }
    
    return 0;
}
