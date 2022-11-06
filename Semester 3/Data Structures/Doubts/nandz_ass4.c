/* 
Assignment 4
Roll Number: 
Name: 

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


struct List* createlist(int vertex)
{
     struct List* l = (struct List*)malloc(sizeof(struct List));
     struct Node* start = (struct Node*)malloc(sizeof(struct Node));
     start->vertex = vertex;
     start->next = NULL;
     l->head = start;
     return l;
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
    }

    if(current->next == NULL)
    {
        node->next = NULL;
        current->next = node;
    }
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
    }
  }

    for(int i = 0; i < numberOfVertices; i++)
    {
        struct Node* current = AdjacencyList[i]->head;

        while(current->next != NULL)
        {
            printf("%d ", current->vertex);
            current = current->next;
        }
        printf("%d\n", current->vertex);
        
    }
    
   return(0);  
}