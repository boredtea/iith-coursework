#include <stdio.h>

int main(int argc, char const *argv[])
{
    int flag = 0;

    double height, weight, BMI;
    int choice;

    while(flag == 0)
    {
        start:
        printf("Enter your height (in m): ");
        scanf("%lf", &height);
        printf("Enter your weight (in kg): ");
        scanf("%lf", &weight);

        if(height < 0 || weight < 0)
        {
            printf("\nInvalid Input\n");
            goto start;

        }

        BMI = weight/(height*height);

        printf("%lf\n", BMI);

        if (BMI > 0 && BMI <= 18.5)
        {
            printf("Underweight\n");
        }   
        else if (BMI > 18.5 && BMI <= 25.0)
        {
            printf("Normal\n");
        }
        else if (BMI > 25.0 && BMI <= 30.0)
        {
            printf("Overweight\n");
        }
        else if (BMI > 30.0)
        {
            printf("Obese\n");
        }
        else
        {
            printf("Invalid Input\n");
        }

        menu:
        printf("Would you like to check BMI again?\n1. Yes\n2. No\nChoice: ");
        scanf("%d", &choice);
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
