#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

void PrintNode(const void *node)
{
    printf("%d\n", *(int *)node);
}

int Compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    Tree *T = createTree();

    for (int i = 0; i < 10; i++)
    {
        Insert(T, &T->start, &i, Compare, sizeof(int));
    }

    int a;

    a = 1;
    printf("Found %d Flag: %d\n", a, Find(T, &a, Compare));
    
    a = 100;
    printf("Found %d Flag: %d\n", a, Find(T, &a, Compare));
    
    a = 6;
    Delete(T, T->start, &a, Compare, sizeof(int));
    printf("Found %d Flag: %d\n", a, Find(T, &a, Compare));
    
    return 0;
}