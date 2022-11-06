/*include necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*partition the array choosing the last element as pivot*/
/*and return the index of the pivot element*/
int partition(int* array, int start, int end){
	/*keep last element at its correct position*/
	int l = start - 1;
	for (int i = start; i < end; ++i)
		if (array[i] < array[end]){
			/*current element is less than pivot element - swap A[l+1] and A[i]*/
			int temp = array[l + 1];
			array[l+1] = array[i];
			array[i] = temp;

			/*increment l*/
			l++;
		}
	/*swap A[l+1] and A[end]*/
	int temp = array[l + 1];
	array[l+1] = array[end];
	array[end] = temp;

	/*return the index of pivot element*/
	return (l + 1);
}

/*sorts the given array of size N using quick sort algorithm*/
void quickSort(int* array, int start, int end){
	/*check if array contains at least two elements to sort*/
	if (start < end){
		/*partition the array and get the pivot index*/
		int pivot_index = partition(array, start, end);
		/*apply quick sort recursively on two parts of the array*/
		quickSort(array, start, pivot_index - 1);
		quickSort(array, pivot_index + 1, end);
	}
}

/*populates the given array of size N with random integers*/
void populateArray(int* array, int N){
	/*seed the random number generator with time*/
	srand(time(NULL));

	/*iterate through all elements in array and populate them*/
	for (int i = 0 ; i < N; ++i)
		array[i] = rand() % 100;
}

/*prints the content of the array to console*/
void printArray(int* array, int N){
	for (int i = 0 ; i < N; ++i)
		printf ("%d ", array[i]);
	printf ("\n");
}

/*driver function: program execution begins from here*/
int main(){
	/*create an array of size 10*/
	int N = 10;
	int array[N];

	/*populate the array with random entries*/
	populateArray(array, N);

	/*print the original content of the array*/
	printf ("Original array: ");
	printArray(array, N);

	/*sort the array using quick sort algorithm*/
	quickSort(array, 0, N-1);

	/*print the sorted content of the array*/
	printf ("Sorted array: ");
	printArray(array, N);

	/*return 0 to caller to indicate normal termination of program*/
	return 0;
}