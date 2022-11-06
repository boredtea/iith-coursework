/*
Assignment 3
Roll Number: CS19BTECH11051
Name: Nandita Lakshmi Tunuguntla
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Structure of each node of Binary Tree
struct Node
{
  char NumberPlate[7];
  struct Node *Parent;
  struct Node *RightChild;
  struct Node *LeftChild;
  int isEmpty;
};

//Structure for the Binary Tree
struct Tree
{
  struct Node *root;
  int nodeCount;
};

//Function to Compare two Strings
int Compare(char A[7], char B[7])
{
  for (int i = 0; i < 7; i++)
  {
    if (A[i] < B[i])
    {
      return 1;
    }
    else if (A[i] > B[i])
    {
      return 0;
    }
  }
  return 2;
}

//Function to allocate space for a tree and place the initial Node
struct Tree *CreateTree()
{
  struct Tree *tree = (struct Tree *)malloc(sizeof(struct Tree));  //Creating space for the tree
  struct Node *dummy = (struct Node *)malloc(sizeof(struct Node)); //Creating Space for the dummy node

  dummy->RightChild = NULL;
  dummy->LeftChild = NULL;
  dummy->Parent = NULL;
  dummy->isEmpty = 1; //The tree is initially empty

  //Placing the dummy node as the root of the tree
  tree->root = dummy;
  tree->nodeCount = 0;
  return tree;
}

//Function to Insert a numberPlate in the tree
void Insert(struct Tree *tree, char numberPlate[7])
{
  int flag = 0; //flag to check if the numberPlate's position is found

  //If dummy node is in the tree make it the root by placing the first numberPlate
  if (tree->root->isEmpty == 1)
  {
    strcpy(tree->root->NumberPlate, numberPlate);
    tree->root->isEmpty = 0;
    tree->nodeCount++;
  }
  //Inserting numberPlate at the right position
  else
  {
    //Creating a newnode for numberPlate
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newnode->NumberPlate, numberPlate);
    newnode->isEmpty = 0;
    newnode->LeftChild = NULL;
    newnode->RightChild = NULL;

    //A node to iterate through the tree
    struct Node *current;
    current = tree->root;

    while (flag == 0)
    {
      //Move to left child if the numberPlate is less than that of current node
      if (Compare(current->NumberPlate, numberPlate) == 0)
      {
        if (current->LeftChild != NULL)
        {
          current = current->LeftChild;
        }
        //Placing newnode in the tree
        else
        {
          current->LeftChild = newnode;
          newnode->Parent = current;

          flag = 1;          //newnode is inserted
          tree->nodeCount++; //Increament the number of nodes of tree
        }
      }
      //Move to right child if the numberPlate is greater than that of current node
      else if (Compare(current->NumberPlate, numberPlate) == 1)
      {
        if (current->RightChild != NULL)
        {
          current = current->RightChild;
        }
        //Placing newnode in the tree
        else
        {
          current->RightChild = newnode;
          newnode->Parent = current;

          flag = 1;          //newnode is inserted
          tree->nodeCount++; //Increament the number of nodes of tree
        }
      }
      else
      {
        break;
      }
    }
  }
}

//Function to Find the numberPlate in tree
void Find(struct Tree *tree, char numberPlate[7])
{
  int found = 0; //Keeps track if the numberPlate is found
  int i = 0;
  char path[tree->nodeCount];
  memset(path, '\0', sizeof(path));

  struct Node *current = tree->root;

  //Till the end of the tree is reached or the node is found
  while (current != NULL)
  {
    //Compare the NumberPlate of current and numberPlate and go down to the left or right child accordingly
    if (Compare(numberPlate, current->NumberPlate) == 1)
    {
      current = current->LeftChild;

      //Mention L in the path after going left
      path[i] = 'L';
      i++;
    }
    else if (Compare(numberPlate, current->NumberPlate) == 0)
    {
      current = current->RightChild;

      //Mention R in the path after going left
      path[i] = 'R';
      i++;
    }
    else
    {
      break;
    }
  }

  if (current == NULL)
  {
    memset(path, '\0', sizeof(path)); //If no node is found then empty the path
  }
  else
  {
    found = 1;
  }

  printf("%d %s\n", found, path);
}

/*Predecessor is the largest value of left Subtree or the last right ansector of the node*/
//Function to find te Predecessor of numberPlate
void Predecessor(struct Tree *tree, char numberPlate[7])
{
  struct Node *predecessor = NULL;
  struct Node *current = tree->root;

  while (current != NULL)
  {
    if (Compare(numberPlate, current->NumberPlate) == 1)
    {
      current = current->LeftChild;
    }
    else if (Compare(numberPlate, current->NumberPlate) == 0)
    {
      predecessor = current; //Before going to RightChild update the possible predessesor (since numberPlate is smaller than that of next)
      current = current->RightChild;
    }
    //numberPlate is found in tree
    else
    {
      //Finding largest value of left subtree if it exists
      if (current->LeftChild != NULL)
      {
        current = current->LeftChild;

        while (current->RightChild != NULL)
        {
          current = current->RightChild;
        }
        predecessor = current;
      }
      break;
    }
  }

  if (predecessor != NULL)
  {
    printf("%s\n", predecessor->NumberPlate);
  }
  else
  {
    printf("0\n");
  }
}

/*Successor is the smallest value of right Subtree or the last left ansector of the node*/
//Function to find te Successor of numberPlate
struct Node *Successor(struct Tree *tree, char numberPlate[7])
{
  struct Node *successor = NULL;
  struct Node *current = tree->root;

  while (current != NULL)
  {
    if (Compare(current->NumberPlate, numberPlate) == 0)
    {
      successor = current; //Before going to LefttChild update successor to the possible successor (since numberPlate is larger than that of next)
      current = current->LeftChild;
    }
    else if (Compare(current->NumberPlate, numberPlate) == 1)
    {
      current = current->RightChild;
    }
    //numberPlate is found in tree
    else
    {
      //Finding the smallest value of right subtree if it exists
      if (current->RightChild != NULL)
      {
        current = current->RightChild;
        while (current->LeftChild != NULL)
        {
          current = current->LeftChild;
        }
        successor = current;
      }
      break;
    }
  }

  return successor;
}

void Delete_Node(struct Tree *tree, struct Node *root, int toPrint)
{
  if (tree->nodeCount >= 1)
  {
    //Root has No Children
    if (root->LeftChild == NULL && root->RightChild == NULL)
    {
      if (toPrint == 1)
      {
        printf("%d\n", 0);
      }

      if (root->Parent == NULL)
      {
        root->isEmpty = 1;
      }
      else if (root->Parent->RightChild == root)
      {
        root->Parent->RightChild = NULL;
        free(root);
      }
      else if (root->Parent->LeftChild == root)
      {
        root->Parent->LeftChild = NULL;
        free(root);
      }
      root = NULL;
      tree->nodeCount--;
    }

    else if (root->LeftChild == NULL || root->RightChild == NULL)
    {
      if (toPrint == 1)
      {
        printf("%d ", 1);
      }

      if (root->LeftChild == NULL)
      {
        if (toPrint == 1)
        {
          printf("%s\n", root->RightChild->NumberPlate);
        }

        if (root->Parent == NULL)
        {
          root->RightChild->Parent = NULL;
          tree->root = root->RightChild;
        }
        else if (root->Parent->RightChild == root)
        {
          root->Parent->RightChild = root->RightChild;
          root->RightChild->Parent = root->Parent;
        }
        else if (root->Parent->LeftChild == root)
        {
          root->Parent->LeftChild = root->RightChild;
          root->RightChild->Parent = root->Parent;
        }
      }
      else if (root->RightChild == NULL)
      {
        if (toPrint == 1)
        {
          printf("%s\n", root->LeftChild->NumberPlate);
        }

        if (root->Parent == NULL)
        {
          root->LeftChild->Parent = NULL;
          tree->root = root->LeftChild;
        }
        else if (root->Parent->RightChild == root)
        {
          root->Parent->RightChild = root->LeftChild;
          root->LeftChild->Parent = root->Parent;
        }
        else if (root->Parent->LeftChild == root)
        {
          root->Parent->LeftChild = root->LeftChild;
          root->LeftChild->Parent = root->Parent;
        }
      }

      free(root);
      root = NULL;
      tree->nodeCount--;
    }
    else
    {
      struct Node *successor = Successor(tree, root->NumberPlate);

      if (toPrint == 1)
      {
        printf("%d %s\n", 2, successor->NumberPlate);
      }

      strcpy(root->NumberPlate, successor->NumberPlate);

      Delete_Node(tree, successor, 0);
    }
  }
}

//Function to Delete a node with numberPlate
void Delete(struct Tree *tree, char numberPlate[7])
{
  struct Node *current = tree->root;

  //Till the end of the tree is reached or the node is found
  while (current != NULL)
  {
    //Compare the NumberPlate of current and numberPlate and go down to the left or right child accordingly
    if (Compare(numberPlate, current->NumberPlate) == 1)
    {
      current = current->LeftChild;
    }
    else if (Compare(numberPlate, current->NumberPlate) == 0)
    {
      current = current->RightChild;
    }
    else
    {
      break;
    }
  }

  //If node is found pass it to Delete_Node function
  if (current == NULL)
  {
    printf("%d\n", -1);
  }
  else
  {
    Delete_Node(tree, current, 1);
  }
}

//Reccursive Function to print the tree InOrder
void Print_Inorder(struct Node *root)
{
  if (root != NULL)
  {
    if (root->isEmpty == 0)
    {
      //Print the LeftChild then the root then the RightChild
      Print_Inorder(root->LeftChild);
      printf("%s ", root->NumberPlate);
      Print_Inorder(root->RightChild);
    }
  }
}

//Reccursive Function to print the tree PreOrder
void Print_Postorder(struct Node *root)
{
  if (root != NULL)
  {
    if (root->isEmpty == 0)
    {
      //Print the LeftChild then the RightChild then the root
      Print_Postorder(root->LeftChild);
      Print_Postorder(root->RightChild);
      printf("%s ", root->NumberPlate);
    }
  }
}

int main()
{
  char choice, numberPlate[7];
  _Bool requests = 0;

  struct Tree *tree = CreateTree();

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
        // *** Call your insert function here with argument numberPlate ***
        Insert(tree, numberPlate);
      }
    }
    else
      break; // choice and numberPlate have values to be processed!!
  }

  do
  { // Ugly do-while to process first request line before first scanf.
    if (choice == 'S')
    {
      //*** Call your search function here with argument numberPlate ***
      Find(tree, numberPlate);
    }
    else if (choice == '<')
    {
      //*** Call your predecessor function here with argument numberPlate ***
      Predecessor(tree, numberPlate);
    }
    else if (choice == '>')
    {
      //*** Call your successor function here with argument numberPlate ***
      struct Node *successor = Successor(tree, numberPlate);
      if (successor != NULL)
      {
        printf("%s\n", successor->NumberPlate);
      }
      else
      {
        printf("0\n");
      }
    }
    else if (choice == '+')
    {
      Insert(tree, numberPlate);
    }
    else if (choice == '-')
    {
      Delete(tree, numberPlate);
    }
    else if (choice == 'I')
    {

      if (tree->root != NULL)
      {
        Print_Inorder(tree->root);
        printf("\n");
      }
    }
    else if (choice == 'P')
    {
      if (tree->root != NULL)
      {
        Print_Postorder(tree->root);

        printf("\n");
      }
    }
  } while (scanf("%*[\n]%c %6s", &choice, numberPlate) != -1);

  return (0);
}