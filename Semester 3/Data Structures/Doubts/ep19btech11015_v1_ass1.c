#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node
{
	struct Node *right;
	struct Node *left;
	struct Node *parent;
	char *plate;
};

struct DataBase
{
	struct Node *root;
};

struct DataBase *create_database()
{
	struct DataBase *database = (struct DataBase *)malloc(sizeof(struct DataBase));
	if (!database)
		return NULL;
	else
		database->root = NULL;
	return database;
}

int comparePlate(char *plate1, char *plate2)
{
	int x;
	int y = 0;
	for (x = 0; x < 6; x++)
	{
		if (plate1[x] != plate2[x])
			break;
	}
	if (plate1[x] == plate2[x])
		y = 1;
	else if (plate1[x] > plate2[x])
		y = 2;
	return y;
}

struct Node *find_node(struct DataBase *database, char *Plate)
{
	struct Node *temp = database->root;
	while (temp != NULL)
	{
		if (comparePlate(temp->plate, Plate) == 0)
			temp = temp->left;
		else if (comparePlate(temp->plate, Plate) == 1)
			return temp;
		else if (comparePlate(temp->plate, Plate) == 2)
			temp = temp->right;
	}
	return temp;
}

char *find_path(struct DataBase *database, char *Plate)
{
	char *buff = NULL;
	int i = 0;
	struct Node *temp = database->root;
	while (temp != NULL)
	{
		if (comparePlate(temp->plate, Plate) == 1)
			return buff;
		else if (comparePlate(temp->plate, Plate) == 2)
		{
			temp = temp->left;
			buff = realloc(buff, sizeof(char) * (i + 1));
			buff[i] = 'R';
		}
		else if (comparePlate(temp->plate, Plate) == 0)
		{
			temp = temp->right;
			buff = realloc(buff, sizeof(char) * (i + 1));
			buff[i] = 'L';
		}
		i++;
	}
	return NULL;
}

void insert_node(struct DataBase *database, char *plate)
{
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	if (!node)
		return;
	node->plate = plate;
	node->parent = node->right = node->left = NULL;
	if (database->root == NULL)
	{
		database->root = node;
		printf("True\n");
	}
	else
	{
		struct Node *temp = database->root;
		while (temp != NULL)
		{
			if (comparePlate(temp->plate, plate) == 2)
			{
				if (temp->right == NULL)
				{
					temp->right = node;
					node->parent = temp;
					printf("True\n");
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
					printf("True\n");
					break;
				}
				else
					temp = temp->left;
			}
		}
	}
	return;
}

int main()
{
	char *firstLine = NULL;
	char *inputLine = NULL;
	size_t length = 0, counter = 0, plateLength = 6;
	char choice, numberPlate[7];
	struct DataBase *database = create_database();
	length = getline(&firstLine, &length, stdin);
	while (counter < length)
	{
		strncpy(numberPlate, &firstLine[counter], plateLength);
		numberPlate[plateLength] = '\0';
		counter = counter + plateLength + 1;
		insert_node(database, numberPlate);
	}
	while (getline(&inputLine, &length, stdin) != -1)
	{
		sscanf(inputLine, "%c %s", &choice, numberPlate);
		if (choice == 'S')
		{
			if (find_node(database, numberPlate) == NULL)
				printf("0\n");
			else
			{
				char *path = find_path(database, numberPlate);
				if (path == NULL)
					printf("1\n");
				else
					printf("1 %s\n", path);
			}
		}
		free(inputLine);
		inputLine = NULL;
		length = 0;
	}
	return 0;
}