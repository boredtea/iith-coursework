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

/*
Function to insert a new vertex in a list
*/
void addEdge(List *L, int vertex, int weight)
{
    //proceed only if new vertex is not the start of the linked list
    if (L->start->vertex != vertex)
    {
        //new nodes which will be inserted into existing strands
        Node *newVertex = (Node *)malloc(sizeof(Node));

        //initialising
        newVertex->vertex = vertex;
        newVertex->weight = weight;
        newVertex->next = NULL;

        //the current pointer will be used to travel to the location where
        //the new vertex is to be inserted
        Node *current = L->start;

        //traversing to required position and inserting the vertex
        while (current->next != NULL && current->next->vertex < newVertex->vertex)
        {
            current = current->next;
        }
        if (current->next == NULL) //inserting at the end
        {
            current->next = newVertex;
            L->vertices++; //increasing length by one
        }
        else if (current->next->vertex != newVertex->vertex) //insering only if node isn't already in the list
        {
            newVertex->next = current->next;
            current->next = newVertex;
            L->vertices++; //increasing length by one
        }
    }
}


PQNode createPQNode(int vertex, int distance)
{
    PQNode newNode;
    newNode.vertex = vertex;
    newNode.distance = distance;
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
    if (priorityQueue[i / 2].distance > priorityQueue[i].distance)
    {
        swap(i, i / 2, priorityQueue);
        bubbleUp(i / 2, priorityQueue);
    }
}

//function to add a vertex to the priority queue
void addVertex(PQNode priorityQueue[], PQNode newVertex)//, int& heapSize)
{
    heapSize++;
    int i = heapSize;
    priorityQueue[i] = newVertex;
    bubbleUp(i, priorityQueue); //finding the correct position of the new event in the heap
}

//function to return the index of the minimum valued child of a parent
int findMinChild(int i, PQNode priorityQueue[])//, int &heapSize)
{
    int index = -1;
    if (heapSize >= (2 * i) && heapSize >= (2 * i + 1))
    {
        if (priorityQueue[2 * i].distance < priorityQueue[2 * i + 1].distance)
            index = 2 * i;
        else
            index = (2 * i) + 1;
    }
    else if (heapSize >= (2 * i)) //only one child case
    {
        if (priorityQueue[2 * i].distance < priorityQueue[i].distance)
            index = 2 * i;
    }
    return index;
}

//function to place a vertex in it's right position in the heap while removing root
void percolateDown(int i, PQNode priorityQueue[])//, int &heapSize)
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
PQNode extractVertex(PQNode priorityQueue[])//, int &heapSize)
{
    PQNode extracted = priorityQueue[1];
    priorityQueue[1] = priorityQueue[heapSize]; //resetting the root as the last event in the queue
    heapSize--;                                 //reducing heap size
    // percolateDown(1, priorityQueue, heapSize);
    percolateDown(1, priorityQueue);

    return extracted;
}


//the "lazy" implementation
void Dijkstra(List *Graph[], int numberOfVertices, int startvertex, int endVertex)
{
    int shortestDistance[numberOfVertices];
    memset(shortestDistance, -1, sizeof(shortestDistance)); //treating -1 like infinity
    shortestDistance[startvertex] = 0;

    //array to store the visited/non-visited status of each vertex during BFS
    //-1: vertex has never been visited
    // 1: vertex has been visited
    int status[numberOfVertices];
    memset(status, -1, sizeof(status));

    PQNode priorityQueue[10 * numberOfVertices];
    heapSize = 0;

    //array to store the shortest path
    PQNode path[numberOfVertices];

    PQNode newVertex = createPQNode(startvertex, shortestDistance[startvertex]);
    // addVertex(priorityQueue, newVertex, heapSize);
    addVertex(priorityQueue, newVertex);

    while (heapSize > 0)
    {
        // PQNode minVertex = extractVertex(priorityQueue, heapSize);
        PQNode minVertex = extractVertex(priorityQueue);

        status[minVertex.vertex] = 1; //the vertex has been visited
        printf("minvertex: %d\n", minVertex.vertex);
        Node *current = Graph[minVertex.vertex]->start;

        for (int i = 0; i < Graph[minVertex.vertex]->vertices - 1; i++)
        {
            current = current->next;
            printf("%d: %d\n", i, current->vertex);
            if (status[current->vertex] == -1)
            {
                if (shortestDistance[current->vertex] == -1)
                    shortestDistance[current->vertex] = current->weight;
                else if (shortestDistance[current->vertex] + current->weight < minVertex.distance)
                    shortestDistance[current->vertex] = shortestDistance[current->vertex] + current->weight;

                newVertex = createPQNode(current->vertex, shortestDistance[current->vertex]);
                // addVertex(priorityQueue, newVertex, heapSize);
                addVertex(priorityQueue, newVertex);
            }
        }
    }

    printf("Distance: %d\n", shortestDistance[endVertex]);
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
    List *Graph[numberOfVertices];

    //declaring priority queue variables
    //Node priorityQueue[10 * numberOfVertices];
    // int heapSize = 0;

    //array to store the visited/non-visited status of each vertex during BFS
    //-1: vertex has never been enqueued
    // 0: vertex is currently in the queue
    // 1: vertex has been dequeued
    //int status[numberOfVertices];

    //allocating memory for a linked list for each vertex
    for (int i = 0; i < numberOfVertices; i++)
        Graph[i] = createList(i);

    int shortestDistance[numberOfVertices];

    while (scanf(" %c", &choice) != -1)
    {
        if (choice == 'N')
        {
            char delimiter;
            scanf("%d", &startVertex);
            while (scanf("%d %d%c", &endVertex, &weight, &delimiter))
            {
                addEdge(Graph[startVertex], endVertex, weight);

                if (delimiter == '\n')
                    break; //Detecting end of line.
            }
        }
        else if (choice == 'D')
        {
            // memset(shortestDistance, -1, sizeof(shortestDistance)); //treating -1 like infinity
            // memset(status, -1, sizeof(status));

            scanf("%d %d", &startVertex, &endVertex);
            Dijkstra(Graph, numberOfVertices, startVertex, endVertex);
        }
    }

    for (int i = 0; i < numberOfVertices; i++)
        printList(Graph[i]);

    //freeing up memory
    for (int i = 0; i < numberOfVertices; i++)
    {
        free(Graph[i]->start);
        Graph[i]->start = NULL;
        free(Graph[i]);
        Graph[i] = NULL;
    }

    return 0;
}