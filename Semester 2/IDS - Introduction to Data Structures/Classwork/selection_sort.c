/*include necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*sorts the given array of size N using selection sort algorithm*/
void selectionSort(int* array, int N){

	for (int i = 0 ; i < N - 1; ++i){
		/*get the minimum element in array[i...N]*/
		/*assume the first element in array[i...N] is minimum*/
		int min_element = array[i];
		int min_index = i;
		/*search for minimum in array[i+1...N]*/
		for (int j = i + 1; j < N; ++j)
			if (array[j] < min_element){
				min_element = array[j];
				min_index = j;
			}
		/*swap array[i] with array[min_index]*/
		int temp = array[i];
		array[i] = array[min_index];
		array[min_index] = temp;
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

	/*sort the array using selection sort algorithm*/
	selectionSort(array, N);

	/*print the sorted content of the array*/
	printf ("Sorted array: ");
	printArray(array, N);

	/*return 0 to caller to indicate normal termination of program*/
	return 0;
}