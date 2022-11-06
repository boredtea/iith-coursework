/* 
Assignment 2
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
    char key[7];
    int children; //stores the number of nodes present under one root
    struct node *parent;
    struct node *leftChild;
    struct node *rightChild;
};
typedef struct node Node;

/*
TREE
The tree struct points to the main root of the tree and stores 
the total number of nodes in the tree.
*/
struct tree
{
    Node *start;
    int length;
};
typedef struct tree Tree;

/**********FUNCTIONS**********/

/*
Function to allocate space in memory to the tree and return a 
pointer to the newly created empty tree.
*/
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

/*
Function to compare the two number plates passed to it.
*/
int compare(char A[7], char B[7])
{
  for (int i = 0; i < 7; i++)
  {
    if (i == 6)
     return 2; // A == B
    else if (A[i] > B[i])
      return 0; // A > B
    else if (A[i] < B[i])
      return 1; //A < B
  }
}


/*
Function to insert a new node in the binary search tree.
*/
void Insert(Tree *T, char key[7])
{
    //creating and initialising the new node to be inserted into the tree
    Node *newnode =  (Node*)malloc(sizeof(Node));
    //newnode->key = key;
    strcpy(newnode->key, key);
    newnode->parent = NULL;
    newnode->leftChild = NULL;
    newnode->rightChild = NULL;

    int flag = 0; //checks if insertion was successful

    Node *current = T->start; //always starts by pointing to the top of the tree

    if(T->length == 0) //case when the tree is empty
    {
        current = T->start;
        T->start = newnode;
        flag = 1; 
    }
    else
    {
        current = T->start;

        //looking for the correct position of the new node
        while(1)
        {
            if(compare(key, current->key) == 1)
            {
                if(current->leftChild != NULL)
                    current = current->leftChild;
                else
                {
                    current->leftChild = newnode;
                    newnode->parent = current; //inserting new node
                    flag = 1;
                    break;
                }
                
            }
            else // if(compare(key, current->key) == 0)
            {
                if(current->rightChild != NULL)
                    current = current->rightChild;
                else
                {
                    current->rightChild = newnode;
                    newnode->parent = current; //inserting new node
                    flag = 1;
                    break;
                }
            }
        }
    }
    if (flag == 1)
        T->length++; 
}

/*
Function to look for a node in the tree and print it's path if found. 
*/
void Search(Tree *T, char key[7])
{
    int depth = 0; //keeps track of the depth of a key
    int flag = 0;  //flag to check whether key exists or not
    char *path = (char*)malloc(T->length * sizeof(char)); 
    memset(path, '\0', sizeof(path));

    Node *current = T->start;
    int i = 0; //iterator for path

    //locating node
    while(1)
    {
        if(compare(key, current->key) == 1) // key < current->key
        {
            if(current->leftChild == NULL)
            {
                break;
            }
            else
            {
                current = current->leftChild;
                //path = realloc(path, (i + 1) * sizeof(char)); 
                path[i++] = 'L';
                depth++;
            } 
        }
        else if(compare(key, current->key) == 0) // key > current->key
        {
            if(current->rightChild == NULL)
            {
                break;
            }
            else
            {
                current = current->rightChild;
                //path = realloc(path, (i + 1) * sizeof(char)); 
                path[i++] = 'R';
                depth++;
            }
        }
        else if(compare(key, current->key) == 2) // key == current->key
        {
            flag = 1;
            break;
        }
    }

    if(flag == 1)
    {
        printf("1 %s\n", path);
    }
    else
    {
        printf("0 \n");
    }
    free(path);
}

/*
Function to locate the node with the maximum value under a given subtree.
*/
Node* LocateMax(Node *root)
{
    //the maximum element will be located in the rightmost branches and will not have a right child
    while(root->rightChild != NULL) 
    {
        root = root->rightChild;
    }
    return root;
}

/*
Function to locate the node with the minimum value under a given subtree.
*/
Node* LocateMin(Node *root)
{
    //the minimum element will be located in the leftmost branches and will not have a left child
    while(root->leftChild != NULL) 
    {
        root = root->leftChild;
    }
    return root;
}

void Successor(Tree *T, char key[7])
{
    Node *root = T->start;
    Node *successor = NULL;

    while(root != NULL)
    {
        //printf("Inside S\n");
        //if key is the same as the root
        //the successor is either the minimum element of the right subtree if it exists
        //or it is the last left ancestor of the root

        if(compare(key, root->key) == 2) //case where right subtree exists
        {
            if(root->rightChild != NULL)
                successor = LocateMin(root->rightChild);
            break;
        }
        else if(compare(key, root->key) == 1) //key < root
        {
            successor = root; //probable or final succesor
            root = root->leftChild; //shifting to left subtree to find a better fit
        }
        else if(compare(key, root->key) == 0) //key > root
        {
            root = root->rightChild;
        }
    }

    if(successor != NULL)
        printf("%s\n", successor->key);
    else
        printf("0\n");  
}

void Predecessor(Tree *T, char key[7])
{
    Node *root = T->start;
    Node *predecessor = NULL;

    while(root != NULL)
    {
        //if key is the same as the root
        //the predecessor is either the maximum element of the left subtree if it exists
        //or it is the 

        if(compare(key, root->key) == 2) //case where left subtree exists
        {
            if(root->leftChild != NULL)
                predecessor = LocateMax(root->leftChild);
            break;
        }
        else if(compare(key, root->key) == 1) //key < root
        {
            root = root->leftChild; //shifting to left subtree to find a better fit
        }
        else if(compare(key, root->key) == 0) //key > root
        {
            predecessor = root; //probable or final predecessor
            root = root->rightChild;
        }
    }

    if(predecessor != NULL)
        printf("%s\n", predecessor->key);
    else
        printf("0\n");  
}

int main()
{
    Tree *T = createTree(); //creating and allocating space to new tree
    
    char *firstLine = NULL;
    char *inputLine = NULL;
    size_t length = 0, counter = 0, plateLength = 6;
    char choice, numberPlate[7];
    _Bool requests = 0;

    // Fetching till we hit the first request
    while (scanf("%s", numberPlate) != -1)
    {
        if (!requests)
        {
            if (strlen(numberPlate) == 1)
            { // Detecting start of request lines.
                choice = numberPlate[0];
                requests = 1;
            }
            else
            {
                Insert(T, numberPlate);

            }
        }
        else
            break; // choice and numberPlate have values to be processed!!
    }

    do
    { // Ugly do-while to process first request line before first scanf.
        if (choice == 'S')
        {
            Search(T, numberPlate);
        }
        else if (choice == '<')
        {
            Predecessor(T, numberPlate);
        }
        else if (choice == '>')
        {
            Successor(T, numberPlate);

        }
    } while (scanf("%*[\n]%c %6s", &choice, numberPlate) != -1);

    free(T);

    return (0);
}