/* 
Assignment 4
Roll Number: EP19BTECH11015
Name: Parth Singh

*/
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *next;
    int vertex;
};

struct Adj_list
{
    int vertex;
    struct Node *head;
    struct Node *tail;
};

struct Adj_list *create_adjlist()
{
    struct Adj_list *adjlist = (struct Adj_list *)malloc(sizeof(struct Adj_list));
    if (!adjlist)
        return NULL;
    adjlist->head = NULL;
    adjlist->tail = NULL;
    return adjlist;
}

struct Node *find_edge(struct Adj_list *adjlist, int endVertex)
{
    if (adjlist->head == NULL)
        return NULL;
    struct Node *node = adjlist->head;
    while (node != NULL != endVertex && node->vertex)
        node = node->next;
    return node;
}

void add_edge_ascending(struct Adj_list *adjlist, int endVertex)
{
    //if (find_edge(adjlist, endVertex) != NULL)
    //	return;
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (!node)
        return;
    node->vertex = endVertex;
    node->next = NULL;
    if (adjlist->head->next == NULL)
        adjlist->head->next = adjlist->tail = node;
    else
    {
        if (adjlist->head->next->vertex > endVertex)
        {
            node->next = adjlist->head->next;
            adjlist->head->next = node;
            adjlist->tail = node;
        }
        else if (adjlist->tail->vertex < endVertex)
        {
            adjlist->tail->next = node;
            adjlist->tail = node;
        }
        else
        {
            struct Node *temp = adjlist->head->next;
            while (temp->next->vertex < endVertex)
                temp = temp->next;
            node->next = temp->next;
            temp->next = node;
        }
    }
}

void append_at_back(struct Adj_list *list, int vert)
{
    if (find_edge(list, vert) != NULL)
        return;
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (!node)
        return;
    node->vertex = vert;
    node->next = NULL;
    if (list->head == NULL)
        list->head = list->tail = node;
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
}

void breadth_first_search(struct Adj_list *graph[], int startVertex, struct Adj_list *explored_list, struct Adj_list *output_list)
{
    if (find_edge(explored_list, startVertex) != NULL)
        return;
    append_at_back(explored_list, startVertex);
    append_at_back(output_list, startVertex);
    struct Node *node = graph[startVertex]->head;
    while (node != NULL)
    {
        breadth_first_search(graph, node->vertex, explored_list, output_list);
        node = node->next;
    }
}

void delete_list(struct Adj_list *list)
{
    struct Node *node = list->head;
    if (node == NULL)
        return;
    if (node->next == NULL)
    {
        list->head = NULL;
        list->tail = NULL;
        free(node);
        node = NULL;
        free(list);
        list = NULL;
    }
    if (node->next != NULL)
    {
        list->head = node->next;
        free(node);
        node = NULL;
        delete_list(list);
    }
}

void print_list(struct Adj_list *list)
{
    if (list->head == NULL)
        return;
    struct Node *node = list->head;
    while (node->next != NULL)
    {
        printf("%d ", node->vertex);
        node = node->next;
    }
    printf("%d\n", node->vertex);
}

int main()
{
    char choice;
    int numberOfVertices, startVertex, endVertex;
    scanf("%d", &numberOfVertices);
    struct Adj_list *graph[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
    {
        graph[i] = create_adjlist();
        struct Node *node = (struct Node *)malloc(sizeof(struct Node));
        node->vertex = i;
        node->next = NULL;
        graph[i]->head = graph[i]->tail = node;
    }
    while (scanf(" %c", &choice) != -1)
    {
        if (choice == 'N')
        {
            char delimiter;
            scanf("%d", &startVertex);
            while (scanf("%d%c", &endVertex, &delimiter))
            {
                add_edge_ascending(graph[startVertex], endVertex);
                add_edge_ascending(graph[endVertex], startVertex);
                if (delimiter == '\n')
                    break;
            }
        }
        else if (choice == 'B')
        {
            scanf("%d", &startVertex);
            struct Adj_list *explored_list = create_adjlist();
            struct Adj_list *output_list = create_adjlist();
            breadth_first_search(graph, startVertex, explored_list, output_list);
            print_list(output_list);
            delete_list(explored_list);
            delete_list(output_list);
        }
    }
    for (int i = 0; i < numberOfVertices; i++)
        delete_list(graph[i]);
    return (0);
}