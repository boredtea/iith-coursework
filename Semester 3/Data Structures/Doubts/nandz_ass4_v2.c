/* 
Assignment 4
Roll Number: CS19BTECH11051
Name: Nandita Lakshmi Tunugunltla
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node
{
    int vertex;
    struct Node* next;
};

struct List
{
    struct Node* head;
};

struct Queue
{
    struct Node* head;
    struct Node* tail;
};


struct List* createlist(int vertex)
{
     struct List* l = (struct List*)malloc(sizeof(struct List));
     struct Node* start = (struct Node*)malloc(sizeof(struct Node));
     start->vertex = vertex;
     start->next = NULL;
     l->head = start;
     return l;
}

struct Queue* createQueue()
{
     struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
     struct Node* dummy = (struct Node*)malloc(sizeof(struct Node));
     dummy->vertex = -1;
     dummy->next = NULL;
     queue->head = dummy;
     queue->tail = dummy;
     return queue;
}



void addEdge(struct List* list, int vertex)
{
    struct Node* current = list->head;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->vertex = vertex;

    while(current->next != NULL)
    {
        if(current->next->vertex < vertex)
        {
            current = current->next;
        }
        else if(current->next->vertex > vertex)
        {
            node->next = current->next;
            current->next = node;
        } 
        else
        {
            break;
        }
    }

    if(current->next == NULL && current->vertex != vertex)
    {
        node->next = NULL;
        current->next = node;
    }

}



void Dequeue(struct Queue* queue)
{
    struct Node* dequeued = queue->head->next;
    queue->head->next = dequeued->next;

    if(dequeued == queue->tail)
    {
        queue->tail = queue->head;
    }

    free(dequeued);
}


void Enqueue(struct Queue* queue, int vertex)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->vertex = vertex;
    node->next = NULL;

    queue->tail->next = node;
    queue->tail = queue->tail->next;

}


void BFS(int numberOfVertices, struct List* AdjacencyList[], int startVertex)
{
    //printf("I'm here!");

    //Keeping track of the vertex position w.r.t queue
    int Vertex[numberOfVertices];                      //-1 if never been in queue, 0 if it is in queue, 1 if it came out of the queue 

    for(int i=0; i < numberOfVertices; i++)
    {
        Vertex[i] = -1;
    }

    struct Queue* queue = createQueue();

    Enqueue(queue, startVertex);
    Vertex[startVertex] = 0;
    printf("%d ", startVertex);

    while (queue->head->next != NULL)
    {
        struct Node* current = AdjacencyList[queue->head->next->vertex]->head;

        while(current->next != NULL)
        {
            current = current->next;

            if(Vertex[current->vertex] == -1)
            {
                Enqueue(queue, current->vertex);
                Vertex[current->vertex] = 0;
                printf("%d ", current->vertex);
            }
        }

        Vertex[queue->head->next->vertex] = 1;
        Dequeue(queue);
        
    }
    printf("\n");
}


int main(){
  char choice;
  int numberOfVertices, startVertex, endVertex;
  
  // Fetching number of vertices
  scanf("%d",&numberOfVertices);

  // Create your adjacency list's array of head vertices here.
  struct List* AdjacencyList[numberOfVertices];

  for(int i = 0; i < numberOfVertices; i++)
  {
    AdjacencyList[i] = createlist(i);
  }
  

  while(scanf(" %c",&choice)!=-1)
  {
    if(choice == 'N')
    {
       char delimiter;

       scanf("%d", &startVertex);    

       while(scanf("%d%c", &endVertex, &delimiter))
       {
	        // Add the edge (startVertex, endVertex) to your graph here.
            addEdge(AdjacencyList[startVertex], endVertex);
            addEdge(AdjacencyList[endVertex], startVertex);
            
	        if(delimiter == '\n') 
            {
                break; // Detecting end of line.
            }
       }
    }
    else if(choice == 'B')
    {
       scanf("%d",&startVertex);

       // Call BFS on your graph starting from startVertex here.
       BFS(numberOfVertices, AdjacencyList, startVertex);

    }
  }

    /*for(int i = 0; i < numberOfVertices; i++)
    {
        struct Node* current = AdjacencyList[i]->head;

        while(current->next != NULL)
        {
            printf("%d ", current->vertex);
            current = current->next;
        }
        printf("%d\n", current->vertex);
        
    }*/

    for (int i = 0; i < numberOfVertices; i++)
    {
        free(AdjacencyList[i]);
    }
    
   return(0);  
}