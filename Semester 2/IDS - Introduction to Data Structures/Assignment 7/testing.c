#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**********STRUCTURES**********/

/*NODE
The node struct helps in making individual nodes of the binary search tree.
One node consists of a pointer to its left and right children, and a pointer to it's parent node.
*/
struct node
{
    int key;
    int children; //stores the number of nodes present under one root
    struct node *parent;
    struct node *leftChild;
    struct node *rightChild;
};
typedef struct node Node;

/*TREE
The tree struct points to the main root of the tree and stores 
the total number of nodes in the tree.*/
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
Tree *createTree()
{
    Tree *T = (Tree *)malloc(sizeof(Tree));
    T->length = 0;
    Node *fakeStart = (Node *)malloc(sizeof(Node));
    fakeStart->leftChild = NULL;
    fakeStart->rightChild = NULL;
    T->start = fakeStart;
    return T;
}

/*
Global pointer to output.txt so that it can be accessed from all functions
*/
FILE *fptr;

/*Function declarations*/

void Insert(Tree *T, Node *root, int key);

int InsertA(Tree *T, Node *root, int key);

Node* InsertB(Tree *T, Node *root, Tree *NewTree, int key);

void checkRight(Tree *L, Tree *R, Node *currentLeft, Node *currentRight, int key);

void checkLeft(Tree *L, Tree *R, Node *currentLeft, Node *currentRight, int key);

void PrintTree(Tree *T);

void Inorder(Node *root);

/*
Function to insert a new node in the binary search tree.
*/

int InsertA(Tree *T, Node *root, int key)
{
    //fptr = fopen("output.txt", "a"); //opening the output file

    if (T->length == 0) //case when the tree is empty
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        newnode->key = key;
        newnode->parent = NULL;
        newnode->leftChild = NULL;
        newnode->rightChild = NULL;
        newnode->children = 0;

        T->start = newnode;
        T->length++;
    }
    if (key == root->key)
        return -1;
    else if (key < root->key)
    {
        if (root->leftChild != NULL)
            Insert(T, root->leftChild, key);
        else
        {
            //creating and initialising the new node to be inserted into the tree
            Node *newnode = (Node *)malloc(sizeof(Node));
            newnode->key = key;
            newnode->parent = NULL;
            newnode->leftChild = NULL;
            newnode->rightChild = NULL;
            newnode->children = 0;

            root->leftChild = newnode;
            newnode->parent = root;
            T->length++;

            return 1;
        }
    }
    else
    {
        if (root->rightChild != NULL)
            Insert(T, root->rightChild, key);
        else
        {
            //creating and initialising the new node to be inserted into the tree
            Node *newnode = (Node *)malloc(sizeof(Node));
            newnode->key = key;
            newnode->parent = NULL;
            newnode->leftChild = NULL;
            newnode->rightChild = NULL;
            newnode->children = 0;

            root->rightChild = newnode;
            newnode->parent = root;
            T->length++;

            return 1;
        }
    }
}

//function to return a pointer to a particular node
Node *FindElement(Node *root, int key)
{
    if (root->key == key)
        return root;

    if (key < root->key)
        FindElement(root->leftChild, key);
    else
        FindElement(root->rightChild, key);
}

void checkRight(Tree *L, Tree *R, Node *currentLeft, Node *currentRight, int key)
{
    int check = 0;

    while (currentRight != NULL && currentRight->leftChild != NULL && currentRight->leftChild->key > key)
    {
        currentRight = currentRight->leftChild;
        //check = 1; //signifies there is rearrangement to be done
    }

    if (currentRight != NULL)
        if (currentRight->leftChild != NULL && currentRight->leftChild->key < key)
        {
            //rearranging links
            currentLeft->rightChild = currentRight->leftChild;
            currentLeft->rightChild->parent = currentLeft;
            currentRight->leftChild = NULL;

            checkLeft(L, R, currentLeft->rightChild, currentRight, key);
        }
}

void checkLeft(Tree *L, Tree *R, Node *currentLeft, Node *currentRight, int key)
{
    int check = 0;

    while (currentLeft != NULL && currentLeft->rightChild != NULL && currentLeft->rightChild->key < key)
    {
        currentLeft = currentLeft->rightChild;
        //check = 1; //signifies there is rearrangement to be done
    }

    if (currentLeft != NULL)
        if (currentLeft->rightChild != NULL && currentLeft->rightChild->key > key)
        {
            //rearranging links
            currentRight->leftChild = currentLeft->rightChild;
            currentRight->leftChild->parent = currentRight;
            currentLeft->rightChild = NULL;

            checkRight(L, R, currentLeft, currentRight->leftChild, key);
        }
}

Node* InsertB(Tree *T, Node *root, Tree *NewTree, int key)
{
    fptr = fopen("output.txt", "a"); //opening the output file

    //creating and initialising the new node to be inserted into the tree
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->key = key;
    newnode->parent = NULL;
    newnode->leftChild = NULL;
    newnode->rightChild = NULL;

    int flag = 0; //checks if insertion was successful
    int side = 0; //-1 if left, 1 if right

    Node *current = root; //always starts by pointing to the top of the tree

    if (key < current->key)
        side = -1;
    else if (key > current->key)
        side = 1;

    if (side == -1)
    {
        while (1)
        {
            if (current->leftChild != NULL && key < current->leftChild->key)
            {
                current = current->leftChild;
            }
            else
            {
                break;
            }
        }
    }
    else if (side == 1)
    {
        while (1)
        {
            if (current->rightChild != NULL && key > current->rightChild->key)
            {
                current = current->rightChild;
            }
            else
            {
                break;
            }
        }
    }

    int check = 0;

    //keep track of the two new subtrees
    Tree *L = createTree(), *R = createTree();

    //current is a pointer to find the correct left or right child
    //of the new node the other child will be the root of the current tree

    NewTree->start = newnode;

    if (side == -1)
    {
        R->start = root;

        if (current->leftChild != NULL)
            L->start = current->leftChild;
        else
            L->start = NULL;
    }
    else if (side == 1)
    {
        L->start = root;

        if (current->rightChild != NULL)
            R->start = current->rightChild;
        else
            R->start = NULL;
    }

    //rearrangement
    Node *currentRight, *currentLeft;
    if (side == 1)
    {
        //finding the first element in the left child that is out of place in the newtree
        currentLeft = FindElement(L->start, current->key);
        currentLeft->rightChild = NULL; //since it is greater than the key and it's in the left subtree
        currentRight = R->start;

        checkRight(L, R, currentLeft, currentRight, key);
        flag = 1;
    }
    else if (side == -1)
    {
        //finding the first element in the right child that is out of place in the newtree
        currentRight = FindElement(R->start, current->key);
        currentRight->leftChild = NULL; //since it is lesser than the key and it's in the right subtree
        currentLeft = L->start;

        checkLeft(L, R, currentLeft, currentRight, key);
        flag = 1;
    }

    //linking the left and right subtrees to the new node
    NewTree->start->leftChild = L->start;
    if (L->start != NULL)
        L->start->parent = NewTree->start;

    NewTree->start->rightChild = R->start;
    if (R->start != NULL)
        R->start->parent = NewTree->start;

    int length = T->length;
    root = NewTree->start;
    T->length = length + 1;


    //printing to the file
    if (flag == 1)
    {
        fprintf(fptr, "true %d\n", (root)->key);
        //fprintf(fptr, "true\n)";
    }
    else
        fprintf(fptr, "false\n");

    fclose(fptr); //closing the output file

    return root;
}


void InorderPrint(Node *root)
{
    if (root->leftChild == NULL && root->rightChild == NULL)
        printf("%d ", root->key);
    else
    {
        if (root->leftChild != NULL)
            Inorder(root->leftChild);

        printf("%d ", root->key);

        if (root->rightChild != NULL)
            Inorder(root->rightChild);
    }
}

void Insert(Tree *T, Node *root, int key)
{
    int n = T->length;
    int random;
    int flag = 0;

    Node *newSubtreeRoot;
    if (n == 0)
        InsertA(T, root, key);
    else
    {
        random = rand() % n + 1; //numbers between 1 to n both included
        if (random > 1)
        {
            flag = InsertA(T, root, key);
            if (flag == 1)
            {
                fptr = fopen("output.txt", "a"); //opening the output file
                fprintf(fptr, "true\n");
                fclose(fptr); //closing the input file
            }
            else if (flag == -1)
            {
                fptr = fopen("output.txt", "a"); //opening the output file
                fprintf(fptr, "false\n");
                fclose(fptr); //closing the input file
            }
        }
        else
        {
            Tree *new = createTree();
            newSubtreeRoot = InsertB(T, root, new, key);

            //inserting the new subtree into the original tree
            root = FindElement(T->start, root->key);
            newSubtreeRoot->parent = root->parent;
            /*if(root->parent->leftChild!= NULL && root->parent->leftChild->key == root->key)
            {
                root->parent->leftChild = newSubtreeRoot;
            }
            else if(root->parent->rightChild!= NULL && root->parent->rightChild->key == root->key)
            {
                root->parent->rightChild = newSubtreeRoot;
            }*/

            if(root->parent != NULL)
            {
                if(root->parent->key < root->key)
                {
                    root->parent->rightChild = newSubtreeRoot;
                }
                if(root->parent->key > root->key)
                {
                    root->parent->leftChild = newSubtreeRoot;
                }
            }
            printf("Inorder: ");
            InorderPrint(T->start);
            printf("\n");
            //root = newSubtreeRoot;
            /*fptr = fopen("output.txt", "a"); 
            fprintf(fptr, "\nnew subtree:\nInorder: ");
            Inorder(newSubtreeRoot);
            fprintf(fptr, "\nFull tree: ");
            Inorder(T->start);
            fprintf(fptr, "\n\n");
            fclose(fptr);*/
        }
    }
}

/*
Function to locate the node with the maximum valueunder a given subtree.
*/
Node *LocateMax(Node *root)
{
    //the maximum element will be located in the rightmost branches and will not have a right child
    while (root->rightChild != NULL)
    {
        root = root->rightChild;
    }
    return root;
}

/*
Funtion to find and delete the selected key from the tree.
*/
int Delete(Tree *T, int key)
{
    int flag = 0; //keeps track of whether the key exists or not

    Node *current = T->start;

    //locating the key
    while (1)
    {
        if (key < current->key)
        {
            if (current->leftChild == NULL)
            {
                break;
            }
            else
            {
                current = current->leftChild;
            }
        }
        else if (key > current->key)
        {
            if (current->rightChild == NULL)
            {
                break;
            }
            else
            {
                current = current->rightChild;
            }
        }
        else if (key == current->key)
        {
            flag = 1;
            break;
        }
    }

    //exiting function if the node doesn't exist
    if (flag == 0)
    {
        return -1;
    }

    //root to be deleted has been located, now deleting

    Node *temp, *parent;

    //node has no children
    if (current->leftChild == NULL && current->rightChild == NULL)
    {
        //resetting the parent node's links
        if (T->length == 1) //case where node has only one node remaining
        {
            temp->leftChild = NULL;
            temp->rightChild = NULL;
            T->start = temp;
        }
        else
        {
            parent = current->parent;
            if (parent->leftChild != NULL && parent->leftChild->key == current->key)
                parent->leftChild = NULL;
            else if (parent->rightChild != NULL && parent->rightChild->key == current->key)
                parent->rightChild = NULL;
        }

        //deallocating memory
        T->length--;
        temp = current;
        free(temp);
        temp = NULL;
    }
    //node has two children
    else if (current->leftChild != NULL && current->rightChild != NULL)
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
        if (current->leftChild == NULL) //node has only right child
        {
            if (parent->leftChild != NULL && parent->leftChild->key == current->key)
            {
                parent->leftChild = current->rightChild; //replacing current node with its right child
            }
            else if (parent->rightChild != NULL && parent->rightChild->key == current->key)
            {
                parent->rightChild = current->rightChild; //replacing current node with its right child
            }
            current->rightChild->parent = parent;
        }
        else if (current->rightChild == NULL) //node has only left child
        {
            if (parent->leftChild != NULL && parent->leftChild->key == current->key)
            {
                parent->leftChild = current->leftChild; //replacing current node with its left child
            }
            else if (parent->rightChild != NULL && parent->rightChild->key == current->key)
            {
                parent->rightChild = current->leftChild; //replacing current node with its left child
            }
            current->leftChild->parent = parent;
        }

        //deallocating memory
        T->length--;
        temp = current;
        free(temp);
        temp = NULL;
    }
    return flag;
}

/*
Function to find a node in the tree. 
*/
int Find(Tree *T, int key)
{
    fptr = fopen("output.txt", "a");

    int depth = 0; //keeps track of the depth of a key
    int flag = 0;  //flag to check whether key exists or not

    Node *current = T->start;

    //locating node
    while (1)
    {
        if (key < current->key)
        {
            if (current->leftChild == NULL)
            {
                break;
            }
            else
            {
                current = current->leftChild;
                depth++;
            }
        }
        else if (key > current->key)
        {
            if (current->rightChild == NULL)
            {
                break;
            }
            else
            {
                current = current->rightChild;
                depth++;
            }
        }
        else if (key == current->key)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        fprintf(fptr, "true, depth=%d\n", depth); //printing to output file
        return depth;
    }
    else
    {
        fprintf(fptr, "false\n"); //printing to output file
        return -1;
    }
    fclose(fptr);
}

/*
FUntion to count number of nodes in the tree rooted at given key.
*/
int children;
void countNodes(Node *root)
{
    Node *current = root;

    if (current->leftChild != NULL)
    {
        children++;
        countNodes(current->leftChild);
    }
    if (current->rightChild != NULL)
    {
        children++;
        countNodes(current->rightChild);
    }
}

/*
Funtion to calculate the difference between number of nodes
in each branch at a given node.
*/
void CalculateImbalance(Tree *T, int key)
{
    fptr = fopen("output.txt", "a");

    int imbalance = 0;

    int leftNodes = 0;
    int rightNodes = 0;

    Node *current = T->start; //used to point to the node containing the key

    while (1)
    {
        if (key < current->key)
        {
            current = current->leftChild;
        }
        else if (key > current->key)
        {
            current = current->rightChild;
        }
        else if (key == current->key)
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
    fprintf(fptr, "%d\n", imbalance);

    fclose(fptr);
}

/*
Functions to print the tree to the file.
*/

//root, left, right
void Preorder(Node *root)
{
    if (root->leftChild == NULL && root->rightChild == NULL)
        fprintf(fptr, "%d ", root->key);
    else
    {
        fprintf(fptr, "%d ", root->key);

        if (root->leftChild != NULL)
            Preorder(root->leftChild);

        if (root->rightChild != NULL)
            Preorder(root->rightChild);
    }
}

//left, root, right
void Inorder(Node *root)
{
    if (root->leftChild == NULL && root->rightChild == NULL)
        fprintf(fptr, "%d ", root->key);
    else
    {
        if (root->leftChild != NULL)
            Inorder(root->leftChild);

        fprintf(fptr, "%d ", root->key);

        if (root->rightChild != NULL)
            Inorder(root->rightChild);
    }
}

//left, right, root
void Postorder(Node *root)
{
    if (root->leftChild == NULL && root->rightChild == NULL)
        fprintf(fptr, "%d ", root->key);
    else
    {
        if (root->leftChild != NULL)
            Postorder(root->leftChild);

        if (root->rightChild != NULL)
            Postorder(root->rightChild);

        fprintf(fptr, "%d ", root->key);
    }
}

void PrintSubTree(Tree *T, int key)
{
    fptr = fopen("output.txt", "a");

    Node *root = T->start; //used to point to the node containing the key

    //locating the key
    while (1)
    {
        if (key < root->key)
        {
            root = root->leftChild;
        }
        else if (key > root->key)
        {
            root = root->rightChild;
        }
        else if (key == root->key)
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

/*
Main function.
*/
int main()
{
    Tree *T = createTree(); //creating and allocating space to new tree
    //T = createTree();
    srand(time(NULL));

    //opening the input file
    FILE *filePointer;
    filePointer = fopen("input.txt", "r");

    //creating output file
    fptr = fopen("output.txt", "w");
    fclose(fptr);

    //setting pointer to the beginning in the input file
    fseek(filePointer, 0, SEEK_SET);

    //reading data from the input file
    char data[10];
    fscanf(filePointer, "%s", data);
    int N = atoi(data);

    int function, key, flag;

    //executing instructions
    for (int i = 1; i <= N; i++)
    {
        fscanf(filePointer, "%s", data);
        function = atoi(data);

        switch (function)
        {
        case 1: //Insert
            fscanf(filePointer, "%s", data);
            key = atoi(data);
            Insert(T, T->start, key);
            break;

        case 2: //Delete
            fscanf(filePointer, "%s", data);
            key = atoi(data);

            fptr = fopen("output.txt", "a");
            flag = Delete(T, key);

            if (flag == 1)
            {
                fprintf(fptr, "true\n");
            }
            else
                fprintf(fptr, "false\n");

            fclose(fptr);
            break;

        case 3: //Find
            fscanf(filePointer, "%s", data);
            key = atoi(data);
            Find(T, key);
            break;

        case 4: //PrintTree
            PrintTree(T);
            printf("Inorder: ");
            InorderPrint(T->start);
            printf("\n");
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
    fclose(filePointer); //closing input file
}