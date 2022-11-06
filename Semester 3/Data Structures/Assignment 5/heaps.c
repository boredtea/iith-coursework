/* 
Assignment 5
Roll Number: ES19BTECH11017
Name: Soumi Chakraborty
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**********STRUCTURES**********/

/*
NODE
The node struct helps in making individual nodes of the binary search tree.
One node consists of a pointer to its left and right children, and a pointer to it's parent node.
*/
struct node
{
    int vertex; //stores the vertex value in a node
    int weight;
    struct node *next; //link to point to next vertex
};
typedef struct node Node;

/*
LIST
The list struct helps in making individual linked lists for each vertex.
*/
struct list
{
    Node *start;  //pointer to mark the head of each linked list
    int vertices; //stores the number of vertices in that particular list
};
typedef struct list List;

struct pqNode
{
    int vertex;
    int distance;
};
typedef struct pqNode PQNode;

/**********FUNCTIONS**********/

/*
Function to allocate space in memory to a List, assign a value as the start 
vertex and return a pointer to the newly created empty list.
*/
List *createList(int startVertex)
{
    List *L = (List *)malloc(sizeof(List));
    Node *head = (Node *)malloc(sizeof(Node));
    head->vertex = startVertex;
    L->vertices = 1;
    head->next = NULL;
    L->start = head; //helps track the starting point of each list
    return L;
}

PQNode createPQNode(int vertex, int distance)
{
    PQNode newNode;
    newNode.vertex = vertex;
    newNode.distance = distance;
    return newNode;
}
int heapSize = 0;

//function to swap two vertices in the priority queue
void swap(int a, int b, PQNode priorityQueue[])
{
    PQNode temp;
    temp = priorityQueue[a];
    priorityQueue[a] = priorityQueue[b];
    priorityQueue[b] = temp;
}

//function to place an event in it's right position in the heap while adding
void bubbleUp(int i, PQNode priorityQueue[])
{
    if ((i - 1 >= 0) && priorityQueue[(i - 1) / 2].distance > priorityQueue[i].distance)
    {
        swap(i, (i - 1) / 2, priorityQueue);
        bubbleUp((i - 1) / 2, priorityQueue);
    }
}

//function to add a vertex to the priority queue
void addVertex(PQNode priorityQueue[], PQNode newVertex) //, int& heapSize)
{
    heapSize++;
    int i = heapSize - 1;
    priorityQueue[i] = newVertex;
    bubbleUp(i, priorityQueue); //finding the correct position of the new event in the heap
}

//function to return the index of the minimum valued child of a parent
int findMinChild(int i, PQNode priorityQueue[]) //, int &heapSize)
{
    int index = -1;
    if (heapSize >= (2 * i + 1) && heapSize >= (2 * i + 2))
    {
        if (priorityQueue[2 * i + 1].distance < priorityQueue[2 * i + 2].distance)
            index = 2 * i + 1;
        else
            index = (2 * i) + 2;
    }
    else if (heapSize >= (2 * i + 1)) //only one child case
    {
        if (priorityQueue[2 * i + 1].distance < priorityQueue[i].distance)
            index = 2 * i + 1;
    }
    return index;
}

//function to place a vertex in it's right position in the heap while removing root
void percolateDown(int i, PQNode priorityQueue[]) //, int &heapSize)
{
    // int minIndex = findMinChild(i, priorityQueue, heapSize);
    int minIndex = findMinChild(i, priorityQueue);
    if (minIndex != -1 && priorityQueue[i].distance > priorityQueue[minIndex].distance)
    {
        swap(i, minIndex, priorityQueue);
        // percolateDown(minIndex, priorityQueue, heapSize);
        percolateDown(minIndex, priorityQueue);
    }
}

//function to extract the highest priority Vertex from the priority queue
PQNode extractVertex(PQNode priorityQueue[]) //, int &heapSize)
{
    PQNode extracted = priorityQueue[0];
    if (heapSize != 1)
    {
        priorityQueue[0] = priorityQueue[heapSize - 1]; //resetting the root as the last event in the queue
        // percolateDown(1, priorityQueue, heapSize);
        percolateDown(0, priorityQueue);
    }
    heapSize--; //reducing heap size

    return extracted;
}

void printList(List *L)
{
    Node *current = L->start;
    while (current != NULL)
    {
        printf("Vertex: %d Weight: %d ", current->vertex, current->weight);
        current = current->next;
    }
    printf("\n");
}

int main()
{
    char choice;
    int numberOfVertices, startVertex, endVertex, weight;

    // Fetching number of vertices
    scanf("%d", &numberOfVertices);
    PQNode priorityQueue[10 * numberOfVertices];

    // for(int i = 0; i < numberOfVertices; i++)
    // {
    //     //printf("%d\n", numberOfVertices-i);
    //     PQNode newNode;
    //     newNode.vertex = i;
    //     newNode.distance = rand()%numberOfVertices;

    //     addVertex(priorityQueue, newNode);
    // }

    PQNode newNode;
    newNode = createPQNode(1, 2);
    addVertex(priorityQueue, newNode);
    newNode = createPQNode(3, 2);
    addVertex(priorityQueue, newNode);
    newNode = createPQNode(4, 3);
    addVertex(priorityQueue, newNode);

    printf("initially\n");
    for (int i = 0; i < heapSize; i++)
    {
        printf("v: %d w: %d\n", priorityQueue[i].vertex, priorityQueue[i].distance);
    }

    extractVertex(priorityQueue);
    printf("extract (1, 2)\n");
    for (int i = 0; i < heapSize; i++)
    {
        printf("v: %d w: %d\n", priorityQueue[i].vertex, priorityQueue[i].distance);
    }
    extractVertex(priorityQueue);
    printf("extract (3, 2)\n");
    for (int i = 0; i < heapSize; i++)
    {
        printf("v: %d w: %d\n", priorityQueue[i].vertex, priorityQueue[i].distance);
    }
    extractVertex(priorityQueue);
    printf("extract (4, 3)\n");
    for (int i = 0; i < heapSize; i++)
    {
        printf("v: %d w: %d\n", priorityQueue[i].vertex, priorityQueue[i].distance);
    }

    return 0;
}