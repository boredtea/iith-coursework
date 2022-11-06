/* 
Assignment 4
Roll Number: ES19BTECH11025
Name: ARSALAN AHMAD SHEIKH

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

void addToList(Node **, int, int);
void breadthFirstSearch(Node **, int, int);

int main()
{
    char choice;
    int numberOfVertices, startVertex, endVertex;

    // Fetching number of vertices
    scanf("%d", &numberOfVertices);

    // Create your adjacency list's array of head vertices here.
    Node *list[numberOfVertices];
    list[numberOfVertices - 1] = NULL;

    while (scanf(" %c", &choice) != EOF)
    {
        if (choice == 'N')
        {
            char delimiter;
            scanf("%d ", &startVertex);
            while (scanf("%d%c", &endVertex, &delimiter))
            {

                // Add the edge (startVertex, endVertex) to your graph here.
                addToList(list, startVertex, endVertex);
                addToList(list, endVertex, startVertex);

                if (delimiter == '\n')
                    break; // Detecting end of line.
            }
        }
        else if (choice == 'B')
        {
            scanf("%d", &startVertex);
            breadthFirstSearch(list, startVertex, numberOfVertices);
        }
    }

    // makeFree(list, size);

    return (0);
}

void addToList(Node **address, int from, int to)
{
    Node *temp = address[from];
    bool inserted = false;
    if (address[from] == NULL)
    {
        address[from] = (Node *)malloc(sizeof(Node));
        address[from]->next = NULL;
        address[from]->value = to;
    }
    else
    {
        if (to < temp->value)
        {
            address[from] = (Node *)malloc(sizeof(Node));
            address[from]->next = temp;
            address[from]->value = to;
        }
        else
        {
            while (temp->next != NULL)
            {
                if (temp->next->value > to)
                {
                    Node *new = (Node *)malloc(sizeof(Node));
                    new->value = to;
                    new->next = temp->next;
                    temp->next = new;
                    inserted = true;
                    break;
                }
                temp = temp->next;
            }
            if (!inserted)
            {
                temp->next = (Node *)malloc(sizeof(Node));
                temp->next->value = to;
                temp->next->next = NULL;
            }
        }
    }
}

void breadthFirstSearch(Node **list, int vertex, int size)
{
    Node *listTraverse;
    Node *queue;
    Node *temp;
    Node *qBreaker;
    int queuedItems = 1;

    queue = (Node *)malloc(sizeof(Node));
    queue->value = vertex;
    queue->next = NULL;
    temp = queue;
    qBreaker = queue;

    bool everQueued[size]; //, isVisited[size];

    for (int i = 0; i < size; i++)
        // everQueued[i] = isVisited[i] = false;
        everQueued[i] = false;

    // everQueued[vertex] = isVisited[vertex] = true;
    everQueued[vertex] = true;

    while (queue != NULL)
    {
        listTraverse = list[vertex];

        // isVisited[vertex] = true;
        everQueued[vertex] = true;
        while (listTraverse != NULL)
        {
            if (everQueued[listTraverse->value] != true)
            {
                everQueued[listTraverse->value] = true;
                queuedItems++;

                temp->next = (Node *)malloc(sizeof(Node));
                temp = temp->next;
                temp->value = listTraverse->value;
                temp->next = NULL;
            }
            listTraverse = listTraverse->next;
        }

        if (queuedItems >= size)
            break;

        qBreaker = qBreaker->next;

        if (qBreaker == NULL)
            break;
        vertex = qBreaker->value;
    }

    while (queue != NULL)
    {
        printf("%d ", queue->value);
        temp = queue;
        queue = queue->next;
        temp->next = NULL;
        free(temp);
    }
    puts("");
}
