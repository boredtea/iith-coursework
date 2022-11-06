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
    int index;
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

/*
PQNODE
The pqNode struct makes up each entity in the priority queue.
*/
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
    else if ((i - 1 >= 0) && priorityQueue[(i - 1) / 2].distance == priorityQueue[i].distance)
    {
        if (priorityQueue[(i - 1) / 2].vertex > priorityQueue[i].vertex)
        {
            swap(i, (i - 1) / 2, priorityQueue);
            bubbleUp((i - 1) / 2, priorityQueue);
        }
    }
}

//function to add a vertex to the priority queue
void addVertex(PQNode priorityQueue[], PQNode newVertex)
{
    heapSize++;
    int i = heapSize - 1;
    priorityQueue[i] = newVertex;
    bubbleUp(i, priorityQueue); //finding the correct position of the new event in the heap
}

//function to return the index of the minimum valued child of a parent
int findMinChild(int i, PQNode priorityQueue[])
{
    int index = -1;

    if ((2 * i + 1) == heapSize - 1) //only one child case
    {
        if (priorityQueue[2 * i + 1].distance < priorityQueue[i].distance)
            index = 2 * i + 1;
        else if (priorityQueue[2 * i + 1].distance == priorityQueue[i].distance)
            index = (priorityQueue[2 * i + 1].vertex < priorityQueue[i].vertex) ? (2 * i + 1) : i;
    }
    else if (heapSize >= (2 * i + 1) && heapSize >= (2 * i + 2))
    {
        if (priorityQueue[2 * i + 1].distance < priorityQueue[2 * i + 2].distance)
            index = 2 * i + 1;
        else if (priorityQueue[2 * i + 1].distance > priorityQueue[2 * i + 2].distance)
            index = (2 * i) + 2;
        else if (priorityQueue[2 * i + 1].distance == priorityQueue[2 * i + 2].distance)
            index = (priorityQueue[2 * i + 1].vertex < priorityQueue[2 * i + 2].vertex) ? (2 * i + 1) : (2 * i + 2);
    }
    return index;
}

//function to place a vertex in it's right position in the heap while removing root
void percolateDown(int i, PQNode priorityQueue[])
{
    int minIndex = findMinChild(i, priorityQueue);
    if (minIndex != -1 && priorityQueue[i].distance > priorityQueue[minIndex].distance)
    {
        swap(i, minIndex, priorityQueue);
        percolateDown(minIndex, priorityQueue);
    }
    else if (minIndex != -1 && priorityQueue[i].distance == priorityQueue[minIndex].distance)
    {
        if (priorityQueue[i].vertex > priorityQueue[minIndex].vertex)
        {
            swap(i, minIndex, priorityQueue);
            percolateDown(minIndex, priorityQueue);
        }
    }
}

//function to extract the highest priority Vertex from the priority queue
PQNode extractVertex(PQNode priorityQueue[])
{
    PQNode extracted = priorityQueue[0];
    priorityQueue[0] = priorityQueue[heapSize - 1]; //resetting the root as the last event in the queue
    percolateDown(0, priorityQueue);

    heapSize--; //reducing heap size

    return extracted;
}

void Dijkstra(List *Graph[], int numberOfVertices, int startVertex, int endVertex)
{
    int flag = 0; //used to break out of the loop
    int shortestDistance[numberOfVertices];
    memset(shortestDistance, -1, sizeof(shortestDistance)); //treating -1 like infinity
    shortestDistance[startVertex] = 0;

    //array to store the visited/non-visited status of each vertex during BFS
    //-1: vertex has never been visited
    // 1: vertex has been visited
    int status[numberOfVertices];
    memset(status, -1, sizeof(status));

    int prevVertex[numberOfVertices];
    prevVertex[startVertex] = -1; //starting vertex

    PQNode priorityQueue[10 * numberOfVertices];
    heapSize = 0;

    PQNode newVertex;
    newVertex = createPQNode(startVertex, shortestDistance[startVertex]);
    addVertex(priorityQueue, newVertex);
    Node *current = Graph[startVertex]->start;

    while (heapSize > 0)
    {
        PQNode minVertex = extractVertex(priorityQueue);

        //breaking out of loop once the endVertex is polled from the PQ
        if (minVertex.vertex == endVertex)
        {
            flag = 1;
            break;
        }

        //skipping if the current vertex has already been visited
        if (status[minVertex.vertex] == 1)
            continue;

        status[minVertex.vertex] = 1; //setting status to visited

        Node *current = Graph[minVertex.vertex]->start;
        for (int i = 0; i < Graph[minVertex.vertex]->vertices - 1; i++)
        {
            current = current->next;
            if (status[current->vertex] == -1)
            {
                if (shortestDistance[current->vertex] == -1 || shortestDistance[minVertex.vertex] + current->weight < shortestDistance[current->vertex])
                {
                    shortestDistance[current->vertex] = shortestDistance[minVertex.vertex] + current->weight;
                    newVertex = createPQNode(current->vertex, shortestDistance[current->vertex]);
                    addVertex(priorityQueue, newVertex);
                    prevVertex[current->vertex] = minVertex.vertex;
                }
            }
        }
    }
    printf("%d ", shortestDistance[endVertex]);

    if (flag == 1)
    {
        int pathReversed[numberOfVertices];
        int i = 0;
        pathReversed[i++] = endVertex;
        int current = prevVertex[endVertex];

        while (current != -1)
        {
            pathReversed[i++] = current;
            current = prevVertex[current];
        }

        //printing path
        for (int j = i - 1; j >= 0; j--)
            printf("%d ", pathReversed[j]);
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

    //allocating memory for a linked list for each vertex
    for (int i = 0; i < numberOfVertices; i++)
        Graph[i] = createList(i);

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
            scanf("%d %d", &startVertex, &endVertex);
            Dijkstra(Graph, numberOfVertices, startVertex, endVertex);
        }
    }

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