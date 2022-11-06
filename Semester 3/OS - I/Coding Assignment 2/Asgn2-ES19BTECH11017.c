#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double average;
int minimum, maximum;

//struct to pass multiple parameters to the functions from pthread_create
struct input
{
    int size;
    int *array;
};
typedef struct input Input;

void *Avg(void *input)
{
    Input *numbers = (Input *)input;
    int sum = 0;
    for (int i = 0; i < numbers->size; i++)
    {
        sum = sum + numbers->array[i];
    }
    average = (double)sum / (double)(numbers->size);
}

void *Min(void *input)
{
    Input *numbers = (Input *)input;
    minimum = numbers->array[0];
    for (int i = 1; i < numbers->size; i++)
    {
        if (numbers->array[i] < minimum)
            minimum = numbers->array[i];
    }
}

void *Max(void *input)
{
    Input *numbers = (Input *)input;
    maximum = numbers->array[0];
    for (int i = 1; i < numbers->size; i++)
    {
        if (numbers->array[i] > maximum)
            maximum = numbers->array[i];
    }
}

int main()
{
    Input input; // stores

    /* Reading from inp.txt */
    FILE *file;
    file = fopen("inp.txt", "r");

    fscanf(file, "%d", &(input.size));
    int numbers[input.size];

    for (int i = 0; i < input.size; i++)
        fscanf(file, "%d", &(numbers[i]));
    input.array = numbers;
    fclose(file);

    pthread_t thread1, thread2, thread3; /* the thread identifier */
    pthread_attr_t attr1, attr2, attr3;  /* set of thread attributes */

    /* set the default attributes of the thread */
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);

    pthread_create(&thread1, &attr1, Avg, (void *)&input); //create the thread
    pthread_join(thread1, NULL);                           //wait for the thread to exit

    pthread_create(&thread2, &attr2, Min, (void *)&input); //create the thread
    pthread_join(thread2, NULL);                           //wait for the thread to exit

    pthread_create(&thread3, &attr3, Max, (void *)&input); //create the thread
    pthread_join(thread3, NULL);                           //wait for the thread to exit

    /* Writing to an output file */
    file = fopen("Asgn2-out-ES19BTECH11017.txt", "w");
    fprintf(file, "The average value is %lf\n", average);
    fprintf(file, "The minimum value is %d\n", minimum);
    fprintf(file, "The maximum value is %d\n", maximum);
    fclose(file);

    return 0;
}