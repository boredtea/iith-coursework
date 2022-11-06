#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**********STRUCTURES**********/

/*NODE
The node struct helps in making individual units of the stack.
One node consists of the lower and higher indices of a subarray,
the line number to which the control of the program returns to,
and a pointer to point to the next unit.
*/
struct node
{
    int lower;
    int higher;
    int lineNumber;
    struct node *next;
};
typedef struct node Node;

/*STACK
The stack struct helps in making building a functioning stack.
It links the nodes together and keeps track of the length of the stack.
*/
struct stack
{
    Node *start;
    int length; //stores length of stack and helps with indentation while printing
};
typedef struct stack Stack;

/**********FUNCTIONS**********/

/*
Function to allocate space in memory to the stack and 
return a pointer to the new, empty stack
*/
Stack *createList()
{
    Stack *S = (Stack *)malloc(sizeof(Stack));
    S->length = 0;
    Node *fakeStart = (Node *)malloc(sizeof(Node));
    fakeStart->next = NULL;
    S->start = fakeStart;
    return S;
}

/*
Function to print the current stack with the proper indentation.
*/
void Print(Stack *S)
{
    //code to create appropriate indentation
    for (int i = 0; i < S->length; i++)
    {
        printf("\t");
    }

    if (S->length > 0)
    {
        Node *current = S->start;
        printf("{"); //start of each line
        for (int i = 0; i < S->length - 1; i++)
        {
            current = current->next;
            printf("(%d, %d, %d), ", current->lower, current->higher, current->lineNumber);
        }
        current = current->next;
        printf("(%d, %d, %d)}\n", current->lower, current->higher, current->lineNumber); //end of each line
    }
    else
    {
        printf("{}\n");
    }
}

/*
Function to push the indices of the subarrays into the stack.
*/
void Push(Stack *S, int lower, int higher, int lineNumber)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->lower = lower;
    newnode->higher = higher;
    newnode->lineNumber = lineNumber;
    newnode->next = NULL;

    //inserting in the beginning
    Node *current = S->start;
    newnode->next = current->next;
    current->next = newnode;

    S->length++; //incrementing length of the stack
}

/*
Function to pop a node from a stack.
*/
void Pop(Stack *S)
{
    //deleting from the beginning
    Node *current = S->start;
    Node *helper = current->next;
    current->next = helper->next;

    S->length--; //decrementing length of the stack
}

Stack *S; //creating a Stack object so that it can be globally accessed

/*
Function to generate a random number between two 
given numbers. This is used for selecting a random pivot.
*/
int randomBetween(int lower, int higher)
{
    srand(time(0)); //seeding

    int random = rand() % (higher - lower);
    random += lower;
    return random;
}

/*
Function to swap two numbers using pointers.
*/
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

/*
Function to partition the given array or subarry into 
further subarrays around the given pivot. 
*/
int partition(int *array, int lower, int higher)
{
    //choosing a random pivot position
    int pivotIndex = randomBetween(lower, higher);
    int pivot = array[pivotIndex];

    swap(&array[pivotIndex], &array[higher]);

    int i = lower - 1;
    for (int j = lower; j <= higher - 1; j++)
    {
        //current element is less than pivot element - swap array[i] and array[j]
        if (array[j] < pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    //swap array[i+1] and array[higher]
    swap(&array[i + 1], &array[higher]);
    return (i + 1);
}

/*
Function to sort the given array or subarray using the quicksort algorithm.
*/
void quickSort(int *array, int lower, int higher, int size)
{
    //check if array contains at least two elements to sort
    if ((lower < higher) && (lower >= 0) && (higher < size))
    {
        //partition the array and get the pivot index
        int pivotIndex = partition(array, lower, higher);

        //apply quick sort recursively on two parts of the array

        /*
        NOTE: __LINE__ returns the line number of the line it is used it. 
        Here, we need to return the line number of the line of code that is 
        executed right after quickSort(), hence __LINE__ + 3.
        */

        Push(S, lower, pivotIndex - 1, (__LINE__ + 3));  //pushing indices of the first subarray and line number to the stack
        Print(S);                                        //printing the modified stack
        quickSort(array, lower, pivotIndex - 1, size);   //sorting the first subarray
        Pop(S);                                          //popping from the stack
        Print(S);                                        //printing the modified stack
        Push(S, pivotIndex + 1, higher, (__LINE__ + 3)); //pushing indices of the second subarray and line number to the stack
        Print(S);                                        //printing the modified stack
        quickSort(array, pivotIndex + 1, higher, size);  //sorting the second subarray
        Pop(S);                                          //popping from the stack
        Print(S);                                        //printing the modified stack
    }
}

/*
Function to print the array.
*/
void printArray(int *array, int N)
{
    for (int i = 0; i < N; ++i)
        printf("%d ", array[i]);

    printf("\n");
}

/*
Main function.
*/
int main()
{
    S = createList(); //allocating memory to Stack object S using createList()

    //taking input and creating the array to be sorted
    int size;
    printf("Enter size of array: ");
    scanf("%d", &size);
    int array[size];

    //checking if user wants to create a random array or enter values
    int choice, flag = 0;
    printf("How would you like to generate your array?\n1. Enter values manually\n2. Generate random array\nChoice: ");
    scanf("%d", &choice);
    while(flag == 0)
    {
        switch(choice)
        {
            case 1:
                for (int i = 0; i < size; i++)
                {
                    printf("Element %d: ", i + 1);
                    scanf("%d", &array[i]);
                }
                flag = 1; //valid choice check
                break;

            case 2:
                srand(time(NULL));
                for (int i = 0; i < size; i++)
                {
                    array[i] = rand() % 100;
                }
                flag = 1; //valid choice check
                break;
            
            default:
                printf("Invalid choice. Enter again: ");
                scanf("%d", &choice);
        }
    }

    

    printf("\nUnsorted array:\n");
    printArray(array, size); //printing unsorted array
    printf("\n");

    Print(S);
    Push(S, 0, size - 1, (__LINE__ + 3)); //pushing indices of the complete, unsorted array to the stack
    Print(S);                             //printing the modified stack
    quickSort(array, 0, size - 1, size);  //sorting the array
    Pop(S);                               //emptying the stack
    Print(S);

    printf("\nSorted array:\n");
    printArray(array, size); //printing the sorted array
    printf("\n");
}
