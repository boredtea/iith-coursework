/*include necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

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

	/*sort the array using insertion sort algorithm*/
	insertionSort(array, N);

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