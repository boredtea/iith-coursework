/*
Assignment 2
Roll Number: EP19BTECH11015
Name: Parth Singh
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct Node //Node of BST containing number-plate information
{
	struct Node* right;
	struct Node* left;
	struct Node* parent;
	char plate[7];
};


struct DataBase //Contains the root of the BST
{
	struct Node* root;
};


struct DataBase* create_database() //To create the database, to store the root
{
	struct DataBase* database = (struct DataBase*)malloc(sizeof(struct DataBase));
	if (database)
		database->root = NULL;
	return database;
}


int comparePlate(char plate1[7], char plate2[7]) //Compare function for the 2 number-plates
{
	int x;
	int y = 0;
	for (x=0; x<6; x++)
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


void insert_node(struct DataBase* database, char Plate[7]) //insert function
{
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	if (!node)
		return;
	for (int i=0; i<7; i++)
		node->plate[i] = Plate[i];
	node->left = node->right = node->parent = NULL;
	if (database->root == NULL)
		database->root = node; //initializing the root if the database is empty
	else
	{ //BST algorithm, just that there is a compare function instead of simple integer comparison
		struct Node* temp = database->root;
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


struct Node* find_node(struct DataBase* database, char Plate[7])
{
	struct Node* temp = database->root;
	while(temp != NULL)
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


void find_path(struct DataBase* database, char Plate[7])
{
	if (find_node(database, Plate) == NULL)
	{
		printf("0\n");
		return;
	}
	printf("1 ");
	struct Node* temp = database->root;
	while(temp != NULL)
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


void direct_successor(struct Node* node, char Plate[7], char succ[7])
{
	if (node == NULL)
	{
		if (comparePlate(succ, Plate) == 2)
			printf("%s\n", succ);
		else
			printf("0\n");
		return;
	}
	else if (comparePlate(node->plate, Plate) == 2)
	{
		if (comparePlate(node->plate, succ) == 2)
			direct_successor(node->left, Plate, succ);
		else
			direct_successor(node->left, Plate, node->left->plate);
	}
	else
	{
		if (comparePlate(node->plate, succ) == 0)
			direct_successor(node->right, Plate, succ);
		else
			direct_successor(node->right, Plate, node->right->plate);
	}
}


void direct_predecessor(struct Node* node, char Plate[7], char succ[7])
{
	if (node == NULL)
	{
		if (comparePlate(succ, Plate) == 0)
			printf("%s\n", succ);
		else
			printf("0\n");
		return;
	}
	else if (comparePlate(node->plate, Plate) == 2)
	{
		if (comparePlate(node->plate, succ) == 2)
			direct_successor(node->right, Plate, succ);
		else
			direct_successor(node->right, Plate, node->plate);
	}
	else
	{
		if (comparePlate(node->plate, succ) == 0)
			direct_successor(node->left, Plate, succ);
		else
			direct_successor(node->left, Plate, node->plate);
	}
}


void delete(struct Node* node)
{
	if (node == NULL)
		return;
	delete(node->left);
	delete(node->right);
	free(node);
	node = NULL;
}


int main() //Driver function, almost same as input module, some minor changes
{
	char* firstLine = NULL;
	char* inputLine = NULL;
	size_t counter = 0;
	char numberPlate[7];
	struct DataBase* database = create_database(); //creating database
	size_t length = getline(&firstLine, &length, stdin);
	while(counter < length)
	{
		strncpy(numberPlate, &firstLine[counter], 6);
		numberPlate[6] = '\0';
		insert_node(database, numberPlate); //calling insert function
		counter = counter + 7;
	}
	printf("\n");
	char choice;
	while(getline(&inputLine, &length, stdin) != -1)
	{
		sscanf(inputLine, " %c %s", &choice, numberPlate);
		if (*inputLine == '\n')
			break;
		numberPlate[6] = '\0';
		if (choice == 'S')
			find_path(database, numberPlate);
		else if (choice == '>')
			direct_successor(database->root, numberPlate, database->root->plate);
		else if (choice == '<')
			direct_predecessor(database->root, numberPlate, database->root->plate);
		free(inputLine);
		inputLine = NULL;
		length = 0;
	}
	delete(database->root);
	free(database);
	database = NULL;
	free(firstLine);
	firstLine = NULL;
	free(inputLine);
	inputLine = NULL;
	return 0;
}