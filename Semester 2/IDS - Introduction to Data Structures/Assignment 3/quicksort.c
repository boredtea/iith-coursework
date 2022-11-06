#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randomBetween(int lower, int higher)
{
    srand(time(NULL));

    int random = rand() % (higher - lower);
    random += lower;
    return random;
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int* array, int lower, int higher)
{
    int pivotIndex = (lower + higher)/2;
    int pivot = array[pivotIndex];

    swap(&array[pivotIndex], &array[higher]);

    int i = lower - 1;
    for(int j = lower; j <= higher - 1; j++)
    {
        //current element is less than pivot element - swap A[i] and A[j]
        if(array[j] < pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[higher]);
    return (i + 1);
}

void quickSort(int* array, int lower, int higher)
{
	//check if array contains at least two elements to sort
	if (lower < higher)
    {
		//partition the array and get the pivot index
		int pivotIndex = partition(array, lower, higher);

		//apply quick sort recursively on two parts of the array
        printf("Lower: %d  Higher: %d\n", lower, pivotIndex - 1);
		quickSort(array, lower, pivotIndex - 1);
        printf("Lower: %d  Higher: %d\n", pivotIndex + 1, higher);
		quickSort(array, pivotIndex + 1, higher);
	}
}

void printArray(int* array, int N)
{
	for (int i = 0 ; i < N; ++i)
		printf("%d ", array[i]);

	printf ("\n");
}

int main()
{
    int size;
    printf("Enter size of array: ");
    scanf("%d", &size);
    int array[size];
    for(int i = 0; i < size; i++)
    {
        printf("Element %d: ", i+1);
        scanf("%d", &array[i]);
    }  

    printArray(array, size);

    printf("Lower: %d  Higher: %d\n", 0, size - 1);
    quickSort(array, 0, size - 1);

    printArray(array, size);
}
