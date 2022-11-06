#include <stdio.h>

int main()
{
    int n1, n2, n3, i, N;
    n1 = 0;
    n2 = 1;

    printf("Enter the number of elements:");
    scanf("%d", &N);

    printf("\n%d %d", n1, n2);

    for (i = 1; i < N; ++i)
    {
        n3 = n1 + n2;
        printf(" %d", n3);

        n1 = n2;
        n2 = n3;
    }
    
    return 0;
}