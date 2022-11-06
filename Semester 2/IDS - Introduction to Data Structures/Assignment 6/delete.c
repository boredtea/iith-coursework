#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int key;
    int children; //stores the number of nodes present under one root
    struct node *parent;
    struct node *leftChild;
    struct node *rightChild;
};
typedef struct node Node;

struct tree
{
    Node *start;
    int length;
};
typedef struct tree Tree;

Tree* createTree()
{
    Tree *T = (Tree*)malloc(sizeof(Tree));
    T->length = 0;
    Node *fakeStart = (Node*)malloc(sizeof(Node));
    fakeStart->leftChild = NULL;
    fakeStart->rightChild = NULL;
    T->start = fakeStart;
    return T;
}

FILE *fptr; //pointer for output.txt

void Insert(Tree *T, int key)
{
    fptr = fopen("output.txt", "a");

    Node *newnode =  (Node*)malloc(sizeof(Node));
    newnode->key = key;
    newnode->parent = NULL;
    newnode->leftChild = NULL;
    newnode->rightChild = NULL;

    int flag = 0; //checks if insertion was successful

    Node *current = T->start; //always starts by pointing to the top of the tree

    if(T->length == 0) //case when the tree is empty
    {
        current = T->start;
        //newnode->next = current->next;
        //current->next = newnode;
        T->start = newnode;
        flag = 1;
        
    }
    else
    {
        current = T->start;

        while(1)
        {
            if(key < current->key)
            {
                if(current->leftChild != NULL)
                    current = current->leftChild;
                else
                {
                    current->leftChild = newnode;
                    newnode->parent = current;
                    flag = 1;
                    break;
                }
                
            }
            else
            {
                if(current->rightChild != NULL)
                    current = current->rightChild;
                else
                {
                    current->rightChild = newnode;
                    newnode->parent = current;
                    flag = 1;
                    break;
                }

            }
        }
    }
    if (flag == 1)
    {
        fprintf(fptr, "true\n");//printf("true\n");
        T->length++;
    }
    else
    fprintf(fptr, "false\n"); //printf("false\n");

    fclose(fptr);
    
}

Node* LocateMax(Node *root)
{
    //the maximum element will be located in the rightmost branches and will not have a right child
    while(root->rightChild != NULL) 
    {
        root = root->rightChild;
    }
    return root;
}

int Delete(Tree *T, int key)
{
    int flag = 0;

    Node *current = T->start;

    while(1)
    {
        if(key < current->key)
        {
            if(current->leftChild == NULL)
            {
                break;
            }
            else
            {
                current = current->leftChild;
            } 
        }
        else if(key > current->key)
        {
            if(current->rightChild == NULL)
            {
                break;
            }
            else
            {
                current = current->rightChild;
            }
        }
        else if(key == current->key)
        {
            flag = 1;
            break;
        }
    }

    if(flag == 0)
    {
        return -1;
    }

    //root to be deleted has been located, now deleting
    Node *temp, *parent;
    //node has no children
    if(current->leftChild == NULL && current->rightChild == NULL)
    {
        printf("Current parent: %d\n", current->parent->key);

        //resetting the parent node's links
        parent = current->parent;
        if(parent->leftChild != NULL && parent->leftChild->key == current->key)
        parent->leftChild = NULL;
        else if(parent->rightChild != NULL && parent->rightChild->key == current->key)
        parent->rightChild = NULL;

        temp = current;
        free(temp);
        temp = NULL;
    }
    //node has two children
    else if(current->leftChild != NULL && current->rightChild != NULL)
    {
        temp = LocateMax(current->leftChild);

        int newValue = temp->key; //storing the new value for the node to be deleted

        //now deleting the node which was rearranged
        Delete(T, temp->key);

        current->key = newValue;
    }
    //node has one child
    else
    {
        //resetting the parent node's links
        parent = current->parent;
        if(current->leftChild == NULL) //node has only right child
        {
           if(parent->leftChild != NULL && parent->leftChild->key == current->key)
           {
               parent->leftChild = current->rightChild; //replacing current node with its right child
           }
           else if(parent->rightChild != NULL && parent->rightChild->key == current->key)
           {
               parent->rightChild = current->rightChild; //replacing current node with its right child
           }
           current->rightChild->parent = parent;
           temp = current;
           free(temp);
           temp = NULL;
        }
        else if(current->rightChild == NULL) //node has only left child
        {
           if(parent->leftChild != NULL && parent->leftChild->key == current->key)
           {
               parent->leftChild = current->leftChild; //replacing current node with its left child

           }
           else if(parent->rightChild != NULL && parent->rightChild->key == current->key)
           {
               parent->rightChild = current->leftChild; //replacing current node with its left child
           }
           current->leftChild->parent = parent;
           temp = current;
           free(temp);
           temp = NULL;
        }

    }
    return flag;
}

int Find(Tree *T, int key)
{
    fptr = fopen("output.txt", "a");

    int depth = 0;
    int flag = 0;

    Node *current = T->start;

    while(1)
    {
        if(key < current->key)
        {
            if(current->leftChild == NULL)
            {
                break;
            }
            else
            {
                current = current->leftChild;
                depth++;
            } 
        }
        else if(key > current->key)
        {
            if(current->rightChild == NULL)
            {
                break;
            }
            else
            {
                current = current->rightChild;
                depth++;
            }
        }
        else if(key == current->key)
        {
            flag = 1;
            break;
        }

    }


    if(flag == 1)
    {
        fprintf(fptr, "true, depth=%d\n", depth);
        //printf("true, depth=%d\n", depth);
        return depth;
    }
    else
    {
        fprintf(fptr, "false\n");
        //printf("false\n");
        return -1;
    }
    fclose(fptr);
}

//counts number of noods in the tree rooted at key
int children;
void countNodes(Node *root)
{
    Node *current = root;

    if(current->leftChild != NULL)
    {
        children++;
        countNodes(current->leftChild);
    }
    if(current->rightChild != NULL)
    {
        children++;
        countNodes(current->rightChild);
    }
}

void CalculateImbalance(Tree *T, int key)
{
    fptr = fopen("output.txt", "a");

    int imbalance = 0;

    int leftNodes = 0;
    int rightNodes = 0;

    Node *current = T->start; //used to point to the node containing the key

    while(1)
    {
        if(key < current->key)
        {
            current = current->leftChild;
        }
        else if(key > current->key)
        {
            current = current->rightChild;
        }
        else if(key == current->key)
        {
            break;
        }
    }

    children = 0;
    countNodes(current->leftChild);
    leftNodes = 1 + children;
    children = 0;
    countNodes(current->rightChild);
    rightNodes = 1 + children;
    children = 0;

    imbalance = leftNodes - rightNodes;
    //printf("%d\n", imbalance);
    fprintf(fptr, "%d\n", imbalance);

    fclose(fptr);
}


//root, left, right
void Preorder(Node *root)
{
    if(root->leftChild == NULL && root->rightChild == NULL)
    fprintf(fptr, "%d ", root->key);
    else
    {
        fprintf(fptr, "%d ", root->key);

        if(root->leftChild != NULL)
        Preorder(root->leftChild);

        if(root->rightChild != NULL)
        Preorder(root->rightChild);
    }
}

//left, root, right
void Inorder(Node *root)
{
    if(root->leftChild == NULL && root->rightChild == NULL)
    fprintf(fptr, "%d ", root->key);
    else
    {
        if(root->leftChild != NULL)
        Inorder(root->leftChild);

        fprintf(fptr, "%d ", root->key);

        if(root->rightChild != NULL)
        Inorder(root->rightChild);
    }  
}

//left, right, root
void Postorder(Node *root)
{
    if(root->leftChild == NULL && root->rightChild == NULL)
    fprintf(fptr, "%d ", root->key);
    else
    {
        if(root->leftChild != NULL)
        Postorder(root->leftChild);

        if(root->rightChild != NULL)
        Postorder(root->rightChild);

        fprintf(fptr, "%d ", root->key);
    }
}


void PrintSubTree(Tree *T, int key)
{
    fptr = fopen("output.txt", "a");

    Node *root = T->start; //used to point to the node containing the key

    while(1)
    {
        if(key < root->key)
        {
            root = root->leftChild;
        }
        else if(key > root->key)
        {
            root = root->rightChild;
        }
        else if(key == root->key)
        {
            break;
        }
    }

    //In-order
    fprintf(fptr, "Inorder: ");
    Inorder(root);
    fprintf(fptr, "\n");

    //Pre-order
    fprintf(fptr, "Preorder: ");
    Preorder(root);
    fprintf(fptr, "\n");

    //Post-order
    fprintf(fptr, "Postorder: ");
    Postorder(root);
    fprintf(fptr, "\n");

    fclose(fptr);
    
}

void PrintTree(Tree *T)
{
    Node *root = T->start; //used to point to the node containing the key
    PrintSubTree(T, root->key);
}

int main()
{
    Tree *T = createTree();
    
    FILE *filePointer;
    filePointer = fopen("input.txt", "r");

    //creating output file
    fptr = fopen("output.txt", "w");
    fclose(fptr);

    fseek(filePointer, 0, SEEK_SET);

    char data[10];
    fscanf(filePointer, "%s", data);
    int N = atoi(data);

    int function, key, flag;
    
    for(int i = 1; i <= N; i++)
    {
        fscanf(filePointer, "%s", data);
        function = atoi(data);

        switch(function)
        {
            case 1: //Insert
                fscanf(filePointer, "%s", data);
                key = atoi(data);
                Insert(T, key);
                break;

            case 2: //Delete
                fscanf(filePointer, "%s", data);
                key = atoi(data);

                fptr = fopen("output.txt", "a");
                flag = Delete(T, key);

                if (flag == 1)
                {
                    fprintf(fptr, "true\n");//printf("true\n");
                    T->length++;
                }
                else
                    fprintf(fptr, "false\n"); //printf("false\n");
                
                fclose(fptr);
                break;

            case 3: //Find
                fscanf(filePointer, "%s", data);
                key = atoi(data);
                Find(T, key);
                break;

            case 4: //PrintTree
                PrintTree(T);
                break;

            case 5: //PrintSubTree
                fscanf(filePointer, "%s", data);
                key = atoi(data);
                PrintSubTree(T, key);
                break;

            case 6: //CalculateImbalance
                fscanf(filePointer, "%s", data);
                key = atoi(data);
                CalculateImbalance(T, key);
                break;

        }
    }
    fclose(filePointer);
    



}