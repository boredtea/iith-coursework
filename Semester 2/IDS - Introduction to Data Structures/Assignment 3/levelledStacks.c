#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int lower;
    int higher;
    int lineNumber;
    struct node *next;
};
typedef struct node Node;

struct stack
{
    Node *start;
    int length;
};
typedef struct stack Stack;
Stack *S;

Stack* createList()
{
    Stack *S = (Stack*)malloc(sizeof(Stack));
    S->length = 0;
    Node *fakeStart = (Node*)malloc(sizeof(Node));
    fakeStart->next = NULL;
    S->start = fakeStart;
    return S;
}

//function to push the indices of the subarrays into the stack
void Push(Stack *S, int lower, int higher)
{
    Node *newnode =  (Node*)malloc(sizeof(Node));
    newnode->lower = lower;
    newnode->higher = higher;
    newnode->next = NULL;

    //inserting in the beginning
    Node *current = S->start;
    newnode->next = current->next;
    current->next = newnode;

    S->length++;

}

//function to pop a node from a stack
void Pop(Stack *S)
{    
    //deleting from the beginning
    Node *current = S->start;
    Node *helper = current->next;
    current->next = helper->next;

    S->length--;
}



void Display(Stack *S, int level)
{
    //code to create appropriate indentation
    for(int i = 1; i <= level; i++)
    {
        printf("\t");
    }

    Node *current = S->start;
    printf("{");
    for(int i = 0; i < S->length - 1; i++)
    {
        current = current->next;
        printf("(%d, %d), ", current->lower, current->higher);
    }
    current = current->next;
    printf("(%d, %d)}\n", current->lower, current->higher);
}


int randomBetween(int lower, int higher)
{
    srand(time(NULL));

    int random = rand() % (higher - lower);
    random += lower;
    return random;
}

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int* array, int lower, int higher)
{
    int pivotIndex = randomBetween(lower, higher);
    int pivot = array[pivotIndex];

    swap(&array[pivotIndex], &array[higher]);

    int i = lower - 1;
    for(int j = lower; j <= higher - 1; j++)
    {
        //current element is less than pivot element - swap A[i] and A[j]
        if(array[j] < pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[higher]);
    return (i + 1);
}

void quickSort(int* array, int lower, int higher)
{
    static int level = 0;
    level++;
	//check if array contains at least two elements to sort
	if (lower < higher)
    {
		//partition the array and get the pivot index
		int pivotIndex = partition(array, lower, higher);

		//apply quick sort recursively on two parts of the array
        Push(S, lower, pivotIndex - 1);
		quickSort(array, lower, pivotIndex - 1);
        Display(S, level);
        Push(S, pivotIndex + 1, higher);
		quickSort(array, pivotIndex + 1, higher);
        Display(S, level);
	}
}

void printArray(int* array, int N)
{
	for (int i = 0 ; i < N; ++i)
		printf("%d ", array[i]);

	printf ("\n");
}

int main()
{
    S = createList();

    int size;
    printf("Enter size of array: ");
    scanf("%d", &size);
    int array[size];
    for(int i = 0; i < size; i++)
    {
        printf("Element %d: ", i+1);
        scanf("%d", &array[i]);
    }  

    printArray(array, size);

    Push(S, 0, size - 1);
    quickSort(array, 0, size - 1);

    printArray(array, size);
}
