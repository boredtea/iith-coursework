#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

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

int Insert(Tree *T, Node **root, void *key, int (*Compare)(const void *, const void *), int size)
{

    //creating and initialising the new node to be inserted into the tree
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->key = key;
    newnode->key = malloc(size);
    memcpy(newnode->key, key, size);
    newnode->parent = NULL;
    newnode->leftChild = NULL;
    newnode->rightChild = NULL;
    newnode->children = 0;

    int flag = 0; //checks if insertion was successful

    Node *current = *root; //always starts by pointing to the top of the tree

    if (T->length == 0) //case when the tree is empty
    {
        current = T->start;
        T->start = newnode;
        flag = 1;
    }
    else
    {
        current = *root;

        //looking for the correct position of the new node
        while (1)
        {
            if (Compare(current->key, key) > 0)
            {
                if (current->leftChild != NULL)
                    current = current->leftChild;
                else
                {
                    current->leftChild = newnode;
                    newnode->parent = current; //inserting new node
                    flag = 1;
                    break;
                }
            }
            else
            {
                if (current->rightChild != NULL)
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
    return flag;
}

Node *LocateMax(Node *root)
{
    //the maximum element will be located in the rightmost branches and will not have a right child
    while (root->rightChild != NULL)
    {
        root = root->rightChild;
    }
    return root;
}

int Delete(Tree *T, Node *root, void *key, int (*Compare)(const void *, const void *), int size)
{
    int flag = 0; //keeps track of whether the key exists or not

    Node *current = root;

    //locating the key
    while (1)
    {
        if (Compare(current->key, key) > 0)
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
        else if (Compare(current->key, key) < 0)
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
        else if (Compare(current->key, key) == 0)
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
            T->start = NULL;
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

        //now deleting the node which was rearranged
        Delete(T, temp, temp->key, Compare, size);
        memcpy(current->key, temp->key, size);

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

int Find(Tree *T, void *key, int (*Compare)(const void *, const void *))
{

    int depth = 0; //keeps track of the depth of a key
    int flag = 0;  //flag to check whether key exists or not

    Node *current = T->start;

    //locating node
    while (1)
    {
        if (Compare(current->key, key) > 0)
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
        else if (Compare(current->key, key) < 0)
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
        else if (Compare(current->key, key) == 0)
        {
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        return depth;
    }
    else
    {
        return -1;
    }
}
