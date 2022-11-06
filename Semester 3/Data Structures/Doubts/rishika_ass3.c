/*
Assignment 3
Roll Number:
Name:
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct node{
  char* val;
  struct node* left;
  struct node* right;
  struct node* parent;
};

struct node* head;

int compare(char* A, char* B){

  for(int i=0; i<6; i++)
  {
    // printf("%c %c\n", A[i], B[i]);
    if(A[i]>B[i])
      return 1;
    if(A[i]<B[i])
      return 0;
    // if(A[i]=B[i])
    //   return 2;
  }

  return 2;
}

void insert(char* numberPlate)
{
  // printf("hi %s",numberPlate);
  if(head==NULL)
  {
    //insert here. next is null;
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->val = strdup(numberPlate);
    // strcpy(temp->val, numberPlate);
    temp->left = NULL;
    temp->right = NULL; 
    temp->parent = NULL;
    head = temp;
    // printf("%s",head->val);
  }
  else
  {
    struct node* current = head;
    int c = 0;

    while(c==0)
    {
      int p = compare(current->val, numberPlate);
      if(p == 0)
      {
        if(current->right == NULL)
        {
          //right;ew
          struct node *temp = (struct node*)malloc(sizeof(struct node));
          // strcpy(temp->val, numberPlate);
          temp->val = strdup(numberPlate);
          temp->left = NULL;
          temp->right = NULL; 
          temp->parent = current;
          current->right = temp;
          break;
        }
        else
        {
          current = current->right;
        }
        
      }
      else
      {
        //left;
        if(current->left == NULL)
        {
          struct node *temp = (struct node*)malloc(sizeof(struct node));
          // strcpy(temp->val, numberPlate);
          temp->val = strdup(numberPlate);
          temp->left = NULL;
          temp->right = NULL;
          temp->parent = current; 
          current->left = temp;
          break;
        }
        else
        {
          current = current->left;
        }
      }
    }
  }

}

int search(char* numberPlate)
{
  struct node* current = head;
  char address[100] = "";
  // printf("%s\n", head->val);
  // printf("%s",current->val);

  while(current!=NULL)
  {
    int p = compare(current->val, numberPlate);

    if(p==0)
    {
      //go right
      current = current->right;
      strcat(address,"R");
    }

    else if(p==1)
    {
      //go left
      current = current->left;
      strcat(address,"L");
    }

    else
    {
      printf("1 %s\n",address);
      return 1; //whatever it's found
    }
  }
  printf("0\n");
  return 0;
}

int countChildren(struct node* node)
{
  if (node->left == NULL && node->right == NULL)
  {
    return 0;
  }
  if (node->left != NULL && node->right != NULL)
  {
    return 2;
  }
  return 1;
}

struct node* find(char* numberPlate)
{
  struct node* current = head;
  // char address[100] = "";
  // printf("%s\n", head->val);
  // printf("%s",current->val);

  while(current!=NULL)
  {
    int p = compare(current->val, numberPlate);

    if(p==0)
    {
      //go right
      current = current->right;
      // strcat(address,"R");
    }

    else if(p==1)
    {
      //go left
      current = current->left;
      // strcat(address,"L");
    }

    else
    {
      // printf("Found %s\n", numberPlate);
      return current; //whatever it's found
    }
  }
  // printf("Not found %s\n", numberPlate);
  return NULL;
}

void delete(char* numberPlate)
{
  struct node* toDel = find(numberPlate);
  if (toDel != NULL)
  {
    struct node* p = toDel->parent;
    if (p->left == toDel)
      p->left = NULL;
    else p->right = NULL;
    free(toDel);
  }
}

struct node* maxValInSubtree(struct node* node)
{
  struct node* c = node;
  while (c->right != NULL)
    c = c->right;
  return c;
}

void predecessorOf(char* numberPlate)
{
  struct node* pred = NULL;
  // printf("hi %s",numberPlate);
  if(head==NULL)
  {
    // nothing in tree, no predessor
    printf("0\n");
  }
  struct node* m = find(numberPlate);
  if (m == NULL)
  {
    insert(numberPlate);
    predecessorOf(numberPlate);
    delete(numberPlate);
    return;
  }
  
  if (m->left != NULL)
  {
    pred = maxValInSubtree(m->left);
    printf("%s\n", pred->val);
    return;
  }

  struct node* root = head;
  struct node* p = m->parent;
  while (p != NULL && m == p->left)
  {
      m = p;
      p = p->parent;
  }
  pred = p;
  if (pred == NULL)
  {
    printf("0\n");
    return;
  }
  printf("%s\n", pred->val);
}

struct node* minValInSubtree(struct node* node)
{
  struct node* c = node;
  while (c->left != NULL)
    c = c->left;
  return c;
}

void successorOf(char* numberPlate)
{
  struct node* succ = NULL;
  // printf("hi %s",numberPlate);
  if(head==NULL)
  {
    // nothing in tree, no successor
    printf("0\n");
  }
  struct node* m = find(numberPlate);
  if (m == NULL)
  {
    insert(numberPlate);
    successorOf(numberPlate);
    delete(numberPlate);
    return;
  }
  if (m->right != NULL)
  {
    succ = minValInSubtree(m->right);
    printf("%s\n", succ->val);
    return;
  }

  struct node* root = head;
  struct node* p = m->parent;
  while (p != NULL && m == p->right)
  {
      m = p;
      p = p->parent;
  }
  succ = p;
  if (succ == NULL)
  {
    printf("0\n");
    return;
  }
  
  printf("%s\n", succ->val);
}

void printCountAndDelete(char* numberPlate)
{
  struct node* toDel = find(numberPlate);
  if (toDel != NULL)
  {
    int n = countChildren(toDel);
    printf("%d ", n);
    if (n > 0)
    {
      if (toDel->left == NULL)
      {
        // Use right
        struct node* t = toDel->right;
        t->parent = toDel->parent;
        if (toDel->parent != NULL)
        {
          if (toDel->parent->left == toDel) toDel->parent->left = t;
          else toDel->parent->right = t;
        } else {
          head = t;
        }
        free(toDel);
        printf("%s\n", t->val);
        return;
      }
      if (toDel->right == NULL)
      {
        // Use left
        struct node* t = toDel->left;
        t->parent = toDel->parent;
        if (toDel->parent != NULL)
        {
          if (toDel->parent->left == toDel) toDel->parent->left = t;
          else toDel->parent->right = t;
        } else {
          head = t;
        }
        free(toDel);
        printf("%s\n", t->val);
        return;
      }
      // If we're here, we have 2 children, need succ
      // Inorder successor is always a leaf node or a node with null left
      struct node* succ = minValInSubtree(toDel->right);
      printf("%s\n", succ->val);
      toDel->val = succ->val;
      if (succ->right != NULL)
      {
        // Use right
        struct node* t = succ->right;
        t->parent = succ->parent;

        if (succ->parent->left == succ) succ->parent->left = t;
        else succ->parent->right = t;
        free(succ);
        // printf("%s\n", t->val);
        return;
      }
      struct node* p = succ->parent;
      if (p->left == succ)
        p->left = NULL;
      else p->right = NULL;
      free(succ);
      return;
    } else {
      // Deleting leaf node
      struct node* p = toDel->parent;
      if (p != NULL) {
        if (p->left == toDel)
          p->left = NULL;
        else p->right = NULL;
      } else {
        // leaf has no parent, must be head
        head = NULL;
      }
      free(toDel);
      printf("\n");
    }
  } else {
    printf("-1\n");
  }
  
}

void printInorder(struct node* root)
{
  if (root != NULL)
  {
    printInorder(root->left);
    printf("%s ", root->val);
    printInorder(root->right);
  }
}

void printPostorder(struct node* root)
{
  if (root != NULL)
  {
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%s ", root->val);
  }
}

int main() {
  char choice, numberPlate[7];
  _Bool requests = 0;
  head = NULL;

  // Fetching till we hit the first request
  while(scanf("%s",numberPlate)!=-1) {
    if(!requests) {
      if(strlen(numberPlate) == 1) { // Detecting start of request lines.
        choice = numberPlate[0];
        requests = 1;
      }
      else {
        insert(numberPlate);
      }
    }
    else break; // choice and numberPlate have values to be processed!!
  }

  do { // Ugly do-while to process first request line before first scanf.
    if(choice == 'S') {
      //*** Call your search function here with argument numberPlate ***
      search(numberPlate);
    }
    else if(choice == '<') {
      //*** Call your predecessor function here with argument numberPlate ***
      predecessorOf(numberPlate);
    }
    else if(choice == '>') {
      //*** Call your successor function here with argument numberPlate ***
      successorOf(numberPlate);
    }
    else if(choice == '+') {
      insert(numberPlate);
    }
    else if(choice == '-') {
      printCountAndDelete(numberPlate);
    }
    else if (choice == 'I') {
      printInorder(head);
      printf("\n");
    }
    else if (choice == 'P') {
      printPostorder(head);
      printf("\n");
    }
  } while (scanf("%*[\n]%c %6s",&choice, numberPlate)!=-1);
  return(0);
}