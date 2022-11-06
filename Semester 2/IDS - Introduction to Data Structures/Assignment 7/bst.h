#ifndef BST_H
#define BST_H

struct node
{
    void *key;
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

Tree *createTree();

int Insert(Tree *T, Node **root, void *key, int (*Compare)(const void*, const void*), int size);

Node *LocateMax(Node *root);

int Delete(Tree *T, Node *root, void *key, int (*Compare)(const void *, const void *), int size);

int Find(Tree *T, void *key, int (*Compare)(const void *, const void *));

#endif