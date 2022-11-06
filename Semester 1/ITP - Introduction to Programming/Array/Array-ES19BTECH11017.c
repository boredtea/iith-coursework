#include <stdio.h>

//function to take input of an integer array with 10 elements
void input(int array[])
{   
    for(int i =  0; i < 10; i++)
    {
        printf("Element [%d]: ", i);
        scanf("%d", &array[i]);

        //loop to check for any duplicate elements being entered
        for(int j = 0; j < i; j++)
        {
            if(array[j] == array[i])
            {
                printf("Duplicate element. Enter element again.\n");
                i--;
                break;
            }
        }
    }
    printf("\n");

}

//function which sorts the passed array using bubble sort
void Sort(int array[], int size)  
{  
    int i, j, temp;  
    for (i = 0; i < size; i++)      
    {  
        for (j = 0; j < size - 1; j++)  
        {
            if (array[j] < array[j+1])  
            {
                temp = array[j];
                array[j]   = array[j+1];
                array[j+1] = temp;
            } 
        }
    }
} 

//function to computeo and display the largest two elements of the array (sorted in descending order) passed to it
void Computatuion(int array[], int size)
{
    int max1, max2;

    switch(size)
    {
        case 0:
            printf("Max_1: doesn't exist.\n");
            printf("Max_2: doesn't exist.\n");
            break;
        case 1:
            printf("Max_1: %d\n", array[0]);
            printf("Max_2: doesn't exist.\n");
            break;
        default:
            printf("Max_1: %d\n", array[0]);
            printf("Max_2: %d\n", array[1]);
            break;
    }
}

//function to find the union of the two sets passed to it
void Union(int a[], int b[], int unionSet[])
{
    //loop to copy all the elements of set a to the union set
    for(int i = 0; i < 10; i++)
    {
        unionSet[i] = a[i];
    }

    int flag = 0; //keeps track of whether a match between two elements has been found or not
    int unionPos = 10; //keeps track of size and current position in the union set

    for(int i = 0; i < 10; i++)
    {
        flag = 0;
        for(int j = 0; j < 10; j++)
        {
            if(b[i] == unionSet[j])
            {
                flag = -1;
                break;
            }
        }
        if(flag == 0)
        {
            unionSet[unionPos] = b[i];
            unionPos++;
        }
    }

    Sort(unionSet, unionPos); //sorting the union set

    printf("\nUnion of sets: \n");
    for(int i = 0; i < unionPos; i++)
    {
        printf("%d  ", unionSet[i]);
    }
    printf("\n\n");

    printf("Maximum elements of the union set: \n");
    Computatuion(unionSet, unionPos);
    
}

void Intersection(int a[], int b[], int intersectionSet[])
{
    int flag = 0; //keeps track of whether a match between two elements has been found or not
    int intersectionPos = 0; //keeps track of size and current position in the intersection set

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(a[i] == b[j])
            {
                intersectionSet[intersectionPos] = a[i];
                intersectionPos++;
                break;
            }
        }
    }

    Sort(intersectionSet, intersectionPos); //sorting the intersection set

    if(intersectionPos == 0)
    {
        printf("\nIntersection of sets: \n");
        printf("\nNULL.\n\n");
    }
    else
    {
        printf("\nIntersection of sets: \n");
        for(int i = 0; i < intersectionPos; i++)
        {
            printf("%d  ", intersectionSet[i]);
        }
        printf("\n\n");
    }

    printf("Maximum elements of the intersection set: \n");
    Computatuion(intersectionSet, intersectionPos);
}


int main(int argc, char const *argv[])
{
    int array1[10], array2[10];
    int unionSet[20]; //maximum size of the union is 20
    int intersectionSet[10]; //maximum size of the intersection is 20

    printf("Enter elements for the first array: \n");
    input(array1);
    printf("Enter elements for the second array: \n");
    input(array2);

    Union(array1, array2, unionSet);
    Intersection(array1, array2, intersectionSet);
    
    return 0;
}
