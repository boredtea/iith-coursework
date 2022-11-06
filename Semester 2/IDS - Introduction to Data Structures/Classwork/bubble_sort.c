/*include necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*sorts the given array of size N using bubble sort algorithm*/
void bubbleSort(int* array, int N){

	for (int i = 0 ; i < N - 1 ; ++i)
		for (int j = 0 ; j < N - i - 1; ++j)
			if (array[j] > array[j + 1]){
				/*swap array[j] and array[j + 1]*/
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
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

	/*sort the array using bubble sort algorithm*/
	bubbleSort(array, N);

	/*print the sorted content of the array*/
	printf ("Sorted array: ");
	printArray(array, N);

	/*return 0 to caller to indicate normal termination of program*/
	return 0;
}