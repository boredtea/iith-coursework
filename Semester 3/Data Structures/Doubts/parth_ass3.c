/* 
Assignment 3
Roll Number: EP19BTECH11015
Name: Parth Singh

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node //Node of BST containing number-plate information
{
	struct Node *right;
	struct Node *left;
	struct Node *parent;
	char plate[7];
};

struct DataBase //Contains the root of the BST
{
	struct Node *root;
};

struct DataBase *create_database() //To create the database, to store the root
{
	struct DataBase *database = (struct DataBase *)malloc(sizeof(struct DataBase));
	if (database)
		database->root = NULL;
	return database;
}

int comparePlate(char plate1[7], char plate2[7]) //Compare function for the 2 number-plates
{
	int x;
	int y = 0;
	for (x = 0; x < 6; x++)
	{
		if (plate1[x] != plate2[x]) //checks till the last character, if finds difference, breaks out immediately
			break;
	}
	if (plate1[x] == plate2[x]) //if the numbers are equal, return 1
		y = 1;
	else if (plate1[x] > plate2[x]) //if 1st number is greater, return 2
		y = 2;
	return y; //return 0 by default, as in the case of 1st number being smaller
}

void insert_node(struct DataBase *database, char Plate[7]) //insert function
{
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	if (!node)
		return;
	for (int i = 0; i < 7; i++)
		node->plate[i] = Plate[i];
	node->left = node->right = node->parent = NULL;
	if (database->root == NULL)
		database->root = node; //initializing the root if the database is empty
	else
	{ //BST algorithm, just that there is a compare function instead of simple integer comparison
		struct Node *temp = database->root;
		while (temp != NULL)
		{
			if (comparePlate(Plate, temp->plate) == 2)
			{
				if (temp->right == NULL)
				{
					temp->right = node;
					node->parent = temp;
					break;
				}
				else
					temp = temp->right;
			}
			else
			{
				if (temp->left == NULL)
				{
					temp->left = node;
					node->parent = temp;
					break;
				}
				else
					temp = temp->left;
			}
		}
	}
	return;
}

struct Node *find_node(struct DataBase *database, char Plate[7])
{
	struct Node *temp = database->root;
	while (temp != NULL)
	{
		if (comparePlate(Plate, temp->plate) == 0)
			temp = temp->left;
		else if (comparePlate(Plate, temp->plate) == 1)
			return temp; //return node when the plates match
		else if (comparePlate(Plate, temp->plate) == 2)
			temp = temp->right;
	}
	return temp; //if plate doesn't match, return NULL
}

void find_path(struct DataBase *database, char Plate[7])
{
	if (find_node(database, Plate) == NULL)
	{
		printf("0\n");
		return;
	}
	printf("1 ");
	struct Node *temp = database->root;
	while (temp != NULL)
	{
		if (comparePlate(temp->plate, Plate) == 1)
			break;
		else if (comparePlate(temp->plate, Plate) == 2)
		{
			temp = temp->left;
			printf("L");
		}
		else if (comparePlate(temp->plate, Plate) == 0)
		{
			temp = temp->right;
			printf("R");
		}
	}
	printf("\n");
	return;
}

void direct_successor(struct Node *node, char Plate[7], char succ[7])
{
	if (node == NULL) //base case
	{
		if (comparePlate(succ, Plate) == 2)
			printf("%s\n", succ);
		else
			printf("0\n");
		return;
	}
	if (comparePlate(node->plate, Plate) == 2)
		direct_successor(node->left, Plate, node->plate);
	else if (comparePlate(node->plate, Plate) == 1)
	{
		if (node->right != NULL)
		{
			struct Node *temp = node->right;
			while (temp->left != 0)
				temp = temp->left;
			strcpy(succ, temp->plate);
		}
		direct_successor(NULL, Plate, succ);
	}
	else if (comparePlate(node->plate, Plate) == 0)
	{
		if (node->right != NULL)
			direct_successor(node->right, Plate, node->right->plate);
		else
			direct_successor(node->right, Plate, succ);
	}
}

void direct_predecessor(struct Node *node, char Plate[7], char pred[7])
{
	if (node == NULL)
	{
		if (comparePlate(pred, Plate) == 0)
			printf("%s\n", pred);
		else
			printf("0\n");
		return;
	}
	if (comparePlate(node->plate, Plate) == 2)
	{
		if (node->left != NULL)
			direct_predecessor(node->left, Plate, node->left->plate);
		else
			direct_predecessor(node->left, Plate, pred);
	}
	else if (comparePlate(node->plate, Plate) == 1)
	{
		if (node->left != NULL)
		{
			struct Node *temp = node->left;
			while (temp->right != 0)
				temp = temp->right;
			strcpy(pred, temp->plate);
		}
		direct_predecessor(NULL, Plate, pred);
	}
	else if (comparePlate(node->plate, Plate) == 0)
		direct_predecessor(node->right, Plate, node->plate);
}

void delete_node_0(struct DataBase *database, struct Node *node)
{
	if (node->parent != NULL)
	{
		if (node->parent->right == node)
			node->parent->right = NULL;
		else
			node->parent->left = NULL;
		free(node);
		node = NULL;
	}
	else
	{
		free(database->root);
		database->root = NULL;
	}
}

void delete_node_1(struct DataBase *database, struct Node *node)
{
	if (node->parent != NULL)
	{
		if (node->parent->right == node)
		{
			if (node->right != NULL)
				node->parent->right = node->right;
			else
				node->parent->right = node->left;
			//node->parent->right->parent = node->parent;
			node->right->parent = node->parent;

		}
		if (node->parent->left == node)
		{
			if (node->right != NULL)
				node->parent->left = node->right;
			else
				node->parent->left = node->left;
			//node->parent->left->parent = node->parent;
			node->left->parent = node->parent;

		}
	}
	else
	{
		if (node->left != NULL)
			database->root = node->left;
		else
			database->root = node->right;
		database->root->parent = NULL;
	}
	free(node);
	node = NULL;
}

void delete_node_2(struct DataBase *database, struct Node *node)
{
	struct Node *temp = node->right;
	while (temp->left != NULL)
		temp = temp->left;
	for (int i = 0; i < 7; i++)
		node->plate[i] = temp->plate[i];
	printf("2 ");
	if (temp->right != NULL)
		delete_node_1(database, temp);
	else
		delete_node_0(database, temp);
	printf("%s\n", node->plate);
}

void delete_node(struct DataBase *database, struct Node *node) //function for deleting a node from the tree
{
	if (node == NULL) //if the numberPlate doesn't exist
		printf("-1\n");
	else //if node is there
	{
		if (node->left == NULL && node->right == NULL)
		{
			printf("0 ");
			delete_node_0(database, node); //function for case 1: 0 children
			printf("\n");
		}
		else if (node->left != NULL && node->right == NULL)
		{
			printf("1 ");
			char *Plate = node->left->plate;
			delete_node_1(database, node); //function for case 2: 1 child
			printf("%s\n", Plate);
		}
		else if (node->left == NULL && node->right != NULL)
		{
			printf("1 ");
			char *Plate = node->right->plate;
			delete_node_1(database, node); //function for case 2: 1 child
			printf("%s\n", Plate);
		}
		else
			delete_node_2(database, node); //function for case 3: 2 children
	}
}

void post_order(struct Node *node) //function for the post-order traversal
{
	if (node == NULL)
		return;
	post_order(node->left);
	post_order(node->right);
	printf("%s ", node->plate);
}

void in_order(struct Node *node) //function for the in-order traversal
{
	if (node == NULL)
		return;
	in_order(node->left);
	printf("%s ", node->plate);
	in_order(node->right);
}

void delete (struct Node *node) //recursive delete function for the whole tree
{
	if (node == NULL)
		return;
	delete (node->left);
	delete (node->right);
	free(node);
	node = NULL;
}

int main() //Driver function, almost same as input module, some minor changes
{
	struct DataBase *database = create_database();
	char choice, numberPlate[7];
	_Bool requests = 0;
	while (scanf("%s", numberPlate) != -1)
	{
		if (!requests)
		{
			if (strlen(numberPlate) == 1)
			{
				choice = numberPlate[0];
				requests = 1;
			}
			else
				insert_node(database, numberPlate);
		}
		else
			break;
	}
	do
	{
		if (choice == 'S')
			find_path(database, numberPlate);
		else if (choice == '<')
			direct_predecessor(database->root, numberPlate, database->root->plate);
		else if (choice == '>')
			direct_successor(database->root, numberPlate, database->root->plate);
		else if (choice == '+') //for adding a node to the database
		{
			if (find_node(database, numberPlate) == NULL)
				insert_node(database, numberPlate);
		}
		else if (choice == '-') //for deleting a node
			delete_node(database, find_node(database, numberPlate));
		else if (choice == 'I') //for in-order traversal
		{
			if (database->root != NULL)
			{
				in_order(database->root);
				printf("\n");
			}
		}
		else if (choice == 'P') //for po-st order traversal
		{
			if (database->root != NULL)
			{
				post_order(database->root);
				printf("\n");
			}
		}
	} while (scanf("%*[\n]%c %6s", &choice, numberPlate) != -1);
	delete (database->root); //deleting whole database
	free(database);
	database = NULL;
	return 0;
}