/*include necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*merges two sorted array to form a new sorted array*/
void merge(int* array, int start, int mid, int end){
	/*take copies of two sorted arrays*/
	int size1 = mid - start + 1;
	int size2 = end - mid;
	int A[size1], B[size2];

	/*copy one part to array A*/
	for (int i = 0 ; i < size1; ++i)
		A[i] = array[start + i];

	/*copy another part to array B*/
	for (int i = 0 ; i < size2; ++i)
		B[i] = array[mid + 1 + i];

	/*indices to iterate through arrays*/
	int a_index = 0, b_index = 0, combinded_index = start;

	/*combine A and B to store in original array*/
	while (a_index  < size1 && b_index < size2){
		if (A[a_index] < B[b_index])
			array[combinded_index++] = A[a_index++];
		else
			array[combinded_index++] = B[b_index++];			
	}

	/*if A is exhausted then copy B entirely*/
	if (a_index == size1)
		while (b_index < size2)
			array[combinded_index++] = B[b_index++];

	/*if B is exhausted then copy A entirely*/
	if (b_index == size2)
		while (a_index < size1)
			array[combinded_index++] = A[a_index++];
}

/*sorts the given array of size N using merge sort algorithm*/
void mergeSort(int* array, int start, int end){
	/*check if array contains at least two elements to be sorted*/
	if (end > start){
		/*divide the array into two equal halves*/
		int mid = (start + end)/2;

		/*sort two halves recursively*/
		mergeSort(array, start, mid);
		mergeSort(array, mid + 1, end);

		/*merge two small sorted array to get a big sorted array*/
		merge(array, start, mid, end);
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

	/*sort the array using merge sort algorithm*/
	mergeSort(array, 0, N-1);

	/*print the sorted content of the array*/
	printf ("Sorted array: ");
	printArray(array, N);

	/*return 0 to caller to indicate normal termination of program*/
	return 0;
}