/*include necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*sorts the given array of size N using insertion sort algorithm*/
void insertionSort(int* array, int N){

	for (int i = 1; i < N; ++i){
		/*take a copy of element to be inserted in sorted array[0...i]*/
		int temp = array[i];

		/*search for the correct position of temp in sorted array[0...i-1]*/
		int j = i - 1;
		while (j >=0 && array[j] > temp){
			/*copy (j)th element to (j+1)th index*/
			array[j+1] = array[j];
			/*decrease the value of j by 1*/
			j--;
		}

		/*paste temp at (j+1)th index*/
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

	/*sort the array using insertion sort algorithm*/
	insertionSort(array, N);

	/*print the sorted content of the array*/
	printf ("Sorted array: ");
	printArray(array, N);

	/*return 0 to caller to indicate normal termination of program*/
	return 0;
}