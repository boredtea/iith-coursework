/* 
Assignment 4
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
    int vertex;        //stores the vertex value in a node
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

/*QUEUE
The queue struct helps in building a functioning queue.
It links the nodes together and keeps track of the length of the queue.
*/
struct queue
{
    Node *start;
    Node *end;
    int length; //stores length of the queue
};
typedef struct queue Queue;

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
Function to allocate space in memory to the queue and 
return a pointer to the new, empty queue
*/
Queue *createQueue()
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->length = 0;
    Node *fakeStart = (Node *)malloc(sizeof(Node));
    fakeStart->next = NULL;
    Q->start = fakeStart;
    Q->end = fakeStart;
    return Q;
}

/*
Function to insert a new vertex in a list
*/
void addEdge(List *L, int vertex)
{
    //proceed only if new vertex is not the start of the linked list
    if (L->start->vertex != vertex)
    {
        //new nodes which will be inserted into existing strands
        Node *newVertex = (Node *)malloc(sizeof(Node));

        //initialising
        newVertex->vertex = vertex;
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

/*
Function to add new vertex to the queue.
*/
void enqueue(Queue *Q, int vertex)
{
    Node *newVertex = (Node *)malloc(sizeof(Node));
    newVertex->vertex = vertex;
    newVertex->next = NULL;

    //inserting in the end
    Node *current;
    //printf("enqueue: %d\n", newVertex->vertex);

    if (Q->length == 0) //case when queue is empty
    {
        //printf("case length 0\n");
        current = Q->start;
        newVertex->next = current->next;
        current->next = newVertex;
        Q->end = newVertex;
    }
    else //all other cases
    {
        current = Q->end;
        newVertex->next = current->next;
        current->next = newVertex;
        Q->end = newVertex;
    }
    Q->length++; //incrementing length of the queue
}

/*
Function to remove a node from the queue.
*/
int dequeue(Queue *Q)
{
    int deleted;
    //deleting from the beginning
    Node *current = Q->start;
    Node *helper = current->next;
    current->next = helper->next;
    if (Q->length == 1)
    {
        Q->end = current;
    }
    Q->length--; //decrementing length of the queue
    deleted = helper->vertex;
    free(helper);
    helper = NULL;
    return deleted;
}

void printList(List *L)
{
    Node *current = L->start;
    while (current != NULL)
    {
        printf("%d ", current->vertex);
        current = current->next;
    }
    printf("\n");
}

void printQueue(Queue *Q)
{
    Node *current = Q->start;
    for(int i = 0; i < Q->length; i++)
    {
        current = current->next;
        printf("%d ", current->vertex);
    }
    printf("\n");
}

void BFS(List *Graph[], int status[], int startVertex, int numberOfVertices)
{

    Queue *Q = createQueue();
    if (status[startVertex] == -1) //enqueuing only if vertex has never been visited
    {
        enqueue(Q, startVertex);
        status[startVertex] = 0; //status 0: vertex is currently in the queue

        int popped; //stores the dequeued vertex
        while (Q->length > 0)
        {
            popped = dequeue(Q);   //dequeueing the first vertex in the queue
            printf("%d ", popped); //printing it
            status[popped] = 1;    //satus 1: vertex has bee visited

            Node *current = Graph[popped]->start;
            //getting all the adjacent vertices of the popped vertex
            for (int i = 1; i < Graph[popped]->vertices; i++)
            {
                current = current->next;
                //enqueuing only if vertex has never been visited
                if (status[current->vertex] == -1)
                {
                    enqueue(Q, current->vertex);
                    status[current->vertex] = 0; //satus 1: vertex has bee visited
                }
            }
        }
    }
    free(Q);
    Q = NULL;
}

int main()
{
    char choice;
    int numberOfVertices, startVertex, endVertex;

    // Fetching number of vertices
    scanf("%d", &numberOfVertices);
    List *Graph[numberOfVertices];

    //array to store the visited/non-visited status of each vertex during BFS
    //-1: vertex has never been enqueued
    // 0: vertex is currently in the queue
    // 1: vertex has been dequeued
    int status[numberOfVertices];

    //allocating memory for a linked list for each vertex
    for (int i = 0; i < numberOfVertices; i++)
        Graph[i] = createList(i);

    while (scanf(" %c", &choice) != -1)
    {
        if (choice == 'N')
        {
            char delimiter;
            scanf("%d", &startVertex);
            while (scanf("%d%c", &endVertex, &delimiter))
            {
                addEdge(Graph[startVertex], endVertex);
                addEdge(Graph[endVertex], startVertex);

                if (delimiter == '\n')
                    break; //Detecting end of line.
            }
        }
        else if (choice == 'B')
        {
            //setting status of every vertex to not-visited
            memset(status, -1, sizeof(status));
            scanf("%d", &startVertex);
            //perform BFS only if the vertex is in the graph
            if (startVertex >= 0 && startVertex < numberOfVertices)
            {
                BFS(Graph, status, startVertex, numberOfVertices);
                printf("\n");
            }
        }
    }
    // for (int i = 0; i < numberOfVertices; i++)
    //     printList(Graph[i]);

    //freeing up memory
    for (int i = 0; i < numberOfVertices; i++)
        free(Graph[i]);
    return 0;
}