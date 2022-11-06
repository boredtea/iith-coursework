/*include necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

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
	int value, flag = 0;

	/*iterate through all elements in array and populate them*/
	for (int i = 0 ; i < N; ++i)
	{
		flag = 0;
		value = rand() % 10000;
		for(int j = 0; j < i; j++)
		{
			if(array[j] == value)
			{
				flag = 1;
				break;
			}
		}
		if(flag == 0)
		array[i] = value;
		else if(flag == 1)
		i--;
	}
	/*Best case:
	for(int i = 0; i < N; i++)
    {
        array[i] = i;
    }*/
	/*Worst case:
	for(int i = 0; i < N; i++)
    {
        array[i] = N - 1 - i;
    }*/
}

/*prints the content of the array to console*/
void printArray(int* array, int N){
	for (int i = 0 ; i < N; ++i)
		printf ("%d ", array[i]);
	printf ("\n");
}

/*driver function: program execution begins from here*/
int main(){

	/*used to get the time before and after the algorithm*/
	struct timeval start, end;
	/*used for computing the time difference*/
	unsigned long long int time1, time2, time_taken;

	/*create an array of size 10*/
	int N = 10000;
	int array[N];

	/*populate the array with random entries*/
	populateArray(array, N);

	/*print the original content of the array*/
	//printf ("Original array: ");
	//printArray(array, N);

	/*get the time before starting the algorithm*/
	gettimeofday(&start, NULL);

	/*sort the array using merge sort algorithm*/
	mergeSort(array, 0, N-1);

	/*get the time after finishing the algorithm*/
	gettimeofday(&end, NULL);

	/*compute the time taken in microseconds*/
	time1 = (start.tv_sec * 1000000 + start.tv_usec);
	time2 = (end.tv_sec * 1000000 + end.tv_usec);

	/*compute the difference in time*/
	time_taken = time2 - time1;

	/*print the sorted content of the array*/
	//printf ("Sorted array: ");
	//printArray(array, N);

	/*print the time taken to console*/
	printf ("Time taken: %lluus\n", time_taken);

	/*return 0 to caller to indicate normal termination of program*/
	return 0;
}