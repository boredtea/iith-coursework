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
    char path[30];
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
}

int main()
{
    Tree *T = createTree(); //creating and allocating space to new tree
    
    char *firstLine = NULL;
    char *inputLine = NULL;
    size_t length = 0, counter = 0, plateLength = 6;
    char choice, numberPlate[7];

    // Fetching only the first line of input.
    length = getline(&firstLine, &length, stdin);

    // Parsing the string word by word.
    while (counter < length)
    {
        strncpy(numberPlate, &firstLine[counter], plateLength);
        numberPlate[plateLength] = '\0';
        counter += plateLength + 1; // The +1 takes care of the space between words.

        Insert(T, numberPlate);
    }

    // Main input handler to serve requests.
    while (getline(&inputLine, &length, stdin) != -1)
    {
        sscanf(inputLine, "%c %s", &choice, numberPlate);
        if (choice == 'S')
        {
            Search(T, numberPlate);
        }
        free(inputLine);
        inputLine = NULL;
        length = 0;
    }
    return 0;
}