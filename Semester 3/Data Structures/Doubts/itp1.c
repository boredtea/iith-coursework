#include <stdio.h>

int main()
{
    long nc;
    nc = 0;
    
    while(getchar() != '\n')
    ++nc;
    
    printf("%ld\n", nc);
    
    return 0;
}
