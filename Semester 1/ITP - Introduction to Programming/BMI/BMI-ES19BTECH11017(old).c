#include <stdio.h>

int main(int argc, char const *argv[])
{
    double height, weight, BMI;
    printf("Enter your height (in m): ");
    scanf("%lf", &height);
    printf("Enter your weight (in kg): ");
    scanf("%lf", &weight);

    BMI = weight/(height*height);

    printf(" %lf\n", BMI);

    if (BMI > 0 && BMI <= 18.5)
    {
        printf("Underweight\n");
    }
    else if (BMI > 18.5 && BMI <= 25)
    {
        printf("Normal\n");
    }
    else if (BMI > 25 && BMI <= 30)
    {
        printf("Overweight\n");
    }
    else if (BMI > 30)
    {
        printf("Obese\n");
    }
    else
    {
        printf("Invalid Input\n");
    }


    return 0;
}
