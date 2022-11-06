#include <stdio.h>

//function to calculate and return hamming distance between two numbers
int hamming(int a, int b)
{
    int differences = a ^ b; //binary XOR returns 1 only when the bits beinng compared are different
    int count_one = 0; 

    //loop to count the number of 1's in 'differences'
    while(differences > 0)
    {
        //checking if the LSB is 1 or 0
        if((differences & 1) == 1) 
            count_one++;

        differences = differences >> 1;
    }
    return count_one;
}
 

int main(int argc, char const *argv[])
{
    int num_1, num_2; //stores input
    int hammingDis; //stores the hamming distance
    int choice, flag = 0; //stores information regarding user's choice and validity of input

    //loop to keep taking input until the user wishes to stop
    while(flag == 0)
    {
        printf("Enter two numbers: ");
        scanf("%d %d", &num_1, &num_2);

        hammingDis = hamming(num_1, num_2);

        printf("The Hamming distance is %d.\n\n", hammingDis);

        //loop to keep taking input until valid input is entered
        while(1)
        {
            printf("Would you like to enter numbers again?\n1. Yes\n2. No\nChoice: ");
            scanf("%d", &choice);

            if(choice == 2)
            {
                printf("Thank you!\n");
                flag = -1;
                break;
            }
            else if(choice == 1)
            break;
            else
            printf("Invalid input! Enter again.\n");
        }
    }
    return 0;
}
