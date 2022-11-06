#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a, b;

    double div;

    printf("Enter two numbers: ");
    scanf("%d%d", &a, &b);

    div = (double)a/(double)b;

    printf("\n%lf\n", div);

    return 0;
}