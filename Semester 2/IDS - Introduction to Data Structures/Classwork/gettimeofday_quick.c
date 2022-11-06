/*include necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

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

	/*sort the array using quick sort algorithm*/
	quickSort(array, 0, N-1);

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