#include <stdio.h>
#include <stdlib.h>

struct node
{
    int info;
    struct node *next;
};
typedef struct node Node;

struct list
{
    Node *start;
    int length;
};
typedef struct list List;

List* createList()
{
    List *L = (List*)malloc(sizeof(List));
    L->length = 0;
    Node *fakeStart = (Node*)malloc(sizeof(Node));
    fakeStart->next = NULL;
    L->start = fakeStart;
    return L;
}

void Insert(List *L, int Data, int position)
{
    Node *newnode =  (Node*)malloc(sizeof(Node));
    newnode->info = Data;
    newnode->next = NULL;
    Node *current = L->start;
    for(int i = 0; i < position - 1; i++)
    {
        current = current->next;
    }
    newnode->next = current->next;
    current->next = newnode;
    L->length++;
    printf("Length of list: %d\n\n", L->length);

}

void Delete(List *L, int position)
{
    if(position == -1)
    {
        printf("ERROR: element doesn't exist.\n");
    }
    else
    {
        Node *current = L->start;
        for(int i = 0; i < position - 1; i++)
        {
            current = current->next;
        }
        Node *helper = current->next;
        current->next = helper->next;
        L->length--;
    }
}

int Find(List *L, int key)
{
    int index = 0;
    int flag = 0;
    Node *current = L->start;
    for(int i = 0; i < L->length; i++)
    {
        current = current->next;
        if(current->info == key)
        {
            flag = 1;
            index = i + 1;
            break;
        }
    }

    if(flag == 1)
    return index;
    else
    return -1;
}

void FindAndDelete(List *L, int key)
{
    int position = Find(L, key);
    if(position == -1)
    printf("ERROR: element doesn't exist.\n");
    else
    {
        Delete(L, position);
    }
}


void Display(List *L)
{
    
    printf("Current list: \n");
    Node *current = L->start;
    for(int i = 0; i < L->length - 1; i++)
    {
        current = current->next;
        printf("%d -> ", current->info);
    }
    current = current->next;
    printf("%d\n\n", current->info);

    current = L->start;
    do
    {
        current = current->next;
        printf("%d ", current->info);
    }while(current->next != NULL);
    printf("\n\n");
    
}


int main()
{
    List *L = createList();

    int info, position, key;
    printf("Enter data for the first elelment: ");
    scanf("%d", &info);

    Insert(L, info, 1);

    

    int choice;
    do
    {
        printf("\n-----------MENU------------\n");
        printf("1. Insert element\n");
        printf("2. Delete element\n");
        printf("3. Find element\n");
        printf("4. Find and delete element\n");
        printf("5. Display list\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
            case 1:
                printf("Enter data: ");
                scanf("%d", &info);
                printf("Enter position: ");
                scanf("%d", &position);
                Insert(L, info, position);
                break;

            case 2:
                printf("Enter position you want to delete: ");
                scanf("%d", &position);
                Delete(L, position);
                break;

            case 3:
                printf("Enter the element you want to find: ");
                scanf("%d", &info);
                key = Find(L, info);
                if(key == -1)
                printf("Element not found!\n");
                else
                printf("Element found at position %d.\n", key);
                break;

            case 4:
                printf("Enter the element you want to find and delete: ");
                scanf("%d", &info);
                FindAndDelete(L, info);
                break;

            case 5:
                Display(L);
                break;

            case 6:
                printf("Bye!\n");
                break;

            default:
                printf("Invalid input! Enter again.\n\n");
            
        }
    }while(choice != 6);
}
