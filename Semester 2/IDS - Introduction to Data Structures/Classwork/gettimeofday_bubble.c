/*include necessary header files*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

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
	int value, flag = 0;

	/iterate through all elements in array and populate them*/
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

	/*sort the array using bubble sort algorithm*/
	bubbleSort(array, N);

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