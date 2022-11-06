#include <stdio.h>
#include <stdlib.h>

/**********STRUCTURES**********/

/*NODE
The node struct helps in making individual DNA nucleotide units.
One node consists of a nucleotide (base), and two pointers to
establish links with its base pair, and the next nucleotide in the strand.
*/
struct node
{
    char base;
    struct node *across; //link to pair with coressponding nucleotide
    struct node *next;   //link to point to next pair of base pairs
};
typedef struct node Node;

/*CHAIN
The chain struct helps in making individual DNA strands (namely alpha and 
beta). It links the nodes together and keeps track of the length of each strand.
*/
struct chain
{
    Node *start; //pointer to mark the head of each DNA strand
    int length;
};
typedef struct chain Chain;

/*MOLECULE
The molecule struct groups an the alpha and beta strand of a DNA molecule together
and thereby 'creates' the molecule. It simultanously helps in creating links with 
other DNA molecules.
*/
struct molecule
{
    struct chain *Alpha;
    struct chain *Beta;
    struct molecule *next;
};
typedef struct molecule Molecule;

/**********FUNCTIONS**********/

/*
Function to allocate space in memory to each chain and 
initialise everything in a Node to a default value
*/
Chain *createChain()
{
    Chain *C = (Chain *)malloc(sizeof(Chain));
    C->length = 0;
    Node *fakeHead = (Node *)malloc(sizeof(Node));
    fakeHead->next = NULL;
    C->start = fakeHead; //helps track the starting point of a DNA strand
    return C;
}

/*
Function to link the alpha chain to the beta chain
*/
void LinkAcross(Chain *A, Chain *B)
{
    Node *currentAlpha = A->start;
    Node *currentBeta = B->start;

    for (int i = 0; i < A->length; i++)
    {
        currentAlpha = currentAlpha->next;
        currentBeta = currentBeta->next;
        currentAlpha->across = currentBeta;
        currentBeta->across = currentAlpha;
    }
}

/*
Function to create and allocate memory for a DNA molecule 
*/
Molecule *createMolecule()
{
    Molecule *newMolecule = (Molecule *)malloc(sizeof(Molecule));

    //creating the chains for the molecule being constructed
    Chain *Alpha = createChain();
    Chain *Beta = createChain();

    LinkAcross(Alpha, Beta);

    //initialising
    newMolecule->Alpha = Alpha;
    newMolecule->Beta = Beta;
    newMolecule->next = NULL;

    return newMolecule;
}

/*
Function to return the corresponding nucleotide for a given nucleotide.
*/
char BasePair(char base)
{
    switch (base)
    {
    case 'A':
        return 'T';
    case 'T':
        return 'A';
    case 'G':
        return 'C';
    case 'C':
        return 'G';
    default:
        return 'X';
    }
}

/*
Function to insert a base-pair into a pre-existing DNA molecule at a given position.
*/
void Insert(int chain_ID, char base, int position, Molecule *Molecule)
{
    //new nodes which will be inserted into existing strands
    Node *newAlpha = (Node *)malloc(sizeof(Node));
    Node *newBeta = (Node *)malloc(sizeof(Node));

    //finding the base pair of the give base
    char basePair = BasePair(base);
    if (chain_ID == 1)
    {
        newAlpha->base = base;
        newBeta->base = basePair;
    }
    else if (chain_ID == 2)
    {
        newBeta->base = base;
        newAlpha->base = basePair;
    }
    //initialising next pointers
    newAlpha->next = NULL;
    newBeta->next = NULL;

    //these current pointers will be used to travel to the location where
    //the new base pair is to be inserted
    Node *currentAlpha = (Molecule->Alpha)->start;
    Node *currentBeta = (Molecule->Beta)->start;

    //traversing to required position and inserting in both the strands
    for (int i = 0; i < position - 1; i++)
    {
        currentAlpha = currentAlpha->next;
        currentBeta = currentBeta->next;
    }
    newAlpha->next = currentAlpha->next;
    currentAlpha->next = newAlpha;
    (Molecule->Alpha)->length++; //increasing length by one
    newBeta->next = currentBeta->next;
    currentBeta->next = newBeta;
    (Molecule->Beta)->length++; //increasing length by one

    //establishing links between alpha and beta
    newAlpha->across = newBeta;
    newBeta->across = newAlpha;
}

/*
Function to delete a base from a DNA strand from a given position.
*/
void Delete(Molecule *Molecule, int position)
{
    if (position == -1) //checking if given position is valid
    {
        printf("ERROR: base pair doesn't exist.\n");
    }
    else
    {
        //these current pointers will be used to travel to the base pair which
        //needs to be deleted
        Node *currentAlpha = (Molecule->Alpha)->start;
        Node *currentBeta = (Molecule->Beta)->start;

        //traversing to required position and deleting from both the strands
        for (int i = 0; i < position - 1; i++)
        {
            currentAlpha = currentAlpha->next;
            currentBeta = currentBeta->next;
        }
        Node *helperAlpha = currentAlpha->next;
        Node *helperBeta = currentBeta->next;
        currentAlpha->next = helperAlpha->next;
        (Molecule->Alpha)->length--; //decreasing length by one
        currentBeta->next = helperBeta->next;
        (Molecule->Beta)->length--; //decreasing length by one
    }
}

/*
Function to split a given DNA chain.
*/
void SplitChain(Molecule *original)
{
    /*
     Splitting a DNA molecule will sequentially separate the alpha and beta strands,
     one base pair at a time. This is somewhat similar to the working mechanism of
     a zipper. This function first separates a base pair, stores them in different 
     molecules, and then regenerates the missing base. After completing this action, 
     moves on to the next base pair.
    */

    //new molecule to store the beta strand of the split molecule, and then regenerate it
    Molecule *replica = createMolecule();

    Node *currentAlpha = (Node *)malloc(sizeof(Node));
    currentAlpha = (original->Alpha)->start;

    Node *currentBeta = (Node *)malloc(sizeof(Node));
    currentBeta = (original->Beta)->start;

    for (int i = 0; i < (original->Alpha)->length; i++)
    {
        currentAlpha = currentAlpha->next;
        currentBeta = currentBeta->next;

        //breaking bonds between the alpha and the beta bases of the original DNA molecule
        currentAlpha->across = NULL;
        currentBeta->across = NULL;
    }
    //sending the separated beta strand to replica
    replica->Beta = original->Beta;
    (replica->Beta)->length = (original->Beta)->length;

    //regenerating the missing strand of each molecule:
    char base;

    Node *current; //helps travelling in the regenerated strand
    //regenerating beta strand for the original molecule
    Chain *regeneratedBeta = createChain();
    current = regeneratedBeta->start;
    currentAlpha = (original->Alpha)->start;
    for (int i = 0; i < (original->Alpha)->length; i++)
    {
        currentAlpha = currentAlpha->next;   //moving to the next nucleotide
        base = BasePair(currentAlpha->base); //finding nucleotide to be regenerated

        Node *newBeta = (Node *)malloc(sizeof(Node));
        newBeta->base = base;
        newBeta->next = NULL;

        newBeta->next = current->next;
        current->next = newBeta;
        current = current->next;
        regeneratedBeta->length++;
    }
    original->Beta = regeneratedBeta;
    (original->Beta)->length = regeneratedBeta->length;
    //linking the original alpha and the regenerated beta strands together
    LinkAcross(original->Alpha, original->Beta);

    //regenerating alpha strand for the replica molecule
    Chain *regeneratedAlpha = createChain();
    current = regeneratedAlpha->start;
    currentBeta = (replica->Beta)->start;
    for (int i = 0; i < (replica->Beta)->length; i++)
    {
        currentBeta = currentBeta->next;    //moving to the next nucleotide
        base = BasePair(currentBeta->base); //finding nucleotide to be regenerated

        Node *newAlpha = (Node *)malloc(sizeof(Node));
        newAlpha->base = base;
        newAlpha->next = NULL;

        newAlpha->next = current->next;
        current->next = newAlpha;
        current = current->next;
        regeneratedAlpha->length++;
    }
    replica->Alpha = regeneratedAlpha;
    (replica->Alpha)->length = regeneratedAlpha->length;
    //linking the replica beta and the regenerated alpha strands together
    LinkAcross(replica->Alpha, replica->Beta);

    //inserting the new molecules into the chain of molecules
    replica->next = original->next;
    original->next = replica;
}

/*
Function to print individual DNA molecules.
*/
void PrintChain(int molecule_ID, Molecule *moleculesList, int length)
{
    //initially, current molecule points to the first DNA molecule in the list
    Molecule *currentMolecule = moleculesList;
    //traversing to the molecule that is to be printed
    for (int i = 1; i < molecule_ID; i++)
        currentMolecule = currentMolecule->next;

    //displaying molecule number
    printf("DNA Molecule %d:  \n", molecule_ID);

    //this node pointer helps in travesing down a chain while printing
    Node *currentAlpha = (currentMolecule->Alpha)->start;

    for (int i = 0; i < (currentMolecule->Alpha)->length; i++)
    {
        currentAlpha = currentAlpha->next; //moving to the next base pair
        printf("%c  --  %c\n", currentAlpha->base, (currentAlpha->across)->base);
    }
    printf("\n");
}

/*
Function to print all existing DNA molecules.
*/
void PrintAllChains(Molecule *moleculesList, int length)
{
    printf("All the DNA molecules so far:  \n");

    for (int i = 1; i <= length; i++)
    {
        PrintChain(i, moleculesList, length);
    }
}

/**********MAIN**********/
int main()
{
    Molecule *firstMolecule = createMolecule(); //acts as the head of the chain of DNA molecules
    Molecule *newMolecule = createMolecule();   //is used to create new molecules after the first one has been created
    Molecule *currentMolecule = firstMolecule;  //is used for travesing through the chain of DNA molecules

    int length = 0; //keeps track of number of DNA molecules

    char base, basePair;
    int position;
    int chain_ID;          //1 for Alpha, 2 for Beta
    int molecule_ID;       //DNA molecule number
    int chain_status = -1; //variable to check if a DNA chain has already been created
    int split_check = 0;   //flag to check if the DNA chain has been split
    int i = 0;             //variable which assists while creating a new chain

    int choice; //stores the users choice from the menu

    //loop to display the menu repeatedly until the user selects to stop
    do
    {
        printf("\n-----------MENU------------\n");
        printf("1. Create Chain\n");
        printf("2. Insert Nucleotide Pair\n");
        printf("3. Delete Nucleotide Pair\n");
        printf("4. Split Chain\n");
        printf("5. Print Chain\n");
        printf("6. Print All Chains\n");
        printf("7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            //case to create new DNA molecules

            if (chain_status == -1) //case to create the first DNA molecule
            {
                length++; //incrementing number of molecules when the first molecule is created
                printf("Select the chain you want to add nucleotides to:\n1. Alpha\n2. Beta\nChoice: ");
                scanf("%d", &chain_ID);
                if ((chain_ID == 1) || (chain_ID == 2)) //check for valid chain ID
                {
                    printf("Enter a sequence of nucleotides (NOTE: first character is the first nucleotide in your chain; enter X to stop):\n");
                    while (base != 'X') //keep taking input until user wishes to stop
                    {
                        while ((base = getchar()) == '\n')
                            ; //taking character input
                        basePair = BasePair(base);
                        if (basePair != 'X') //check for valid base pair
                        {
                            i++; //increment position
                            Insert(chain_ID, base, i, firstMolecule);
                            chain_status = 0; //flag to indicate the first molecule has been created
                        }
                        else
                        {
                            if (base != 'X')
                                printf("Invalid nucleotide, enter again: ");
                        }
                    }
                }
                else
                {
                    printf("ERROR: Invalid Chain ID.\n\n");
                    break;
                }
            }
            else if (chain_status != -1) //case to create the later DNA molecule
            {
                printf("Select the chain you want to add nucleotides to:\n1. Alpha\n2. Beta\nChoice: ");
                scanf("%d", &chain_ID);
                if ((chain_ID == 1) || (chain_ID == 2)) //check for valid chain ID
                {
                    i = 0;
                    base = 'A'; //dummy value
                    printf("Enter a sequence of nucleotides (NOTE: first character is the first nucleotide in your chain; enter X to stop):\n");
                    while (base != 'X') //keep taking input until user wishes to stop
                    {
                        while ((base = getchar()) == '\n')
                            ; //taking character input
                        basePair = BasePair(base);
                        if (basePair != 'X') //check for valid base pair
                        {
                            i++; //increment position
                            Insert(chain_ID, base, i, newMolecule);

                            //chain_status = 0; //flag to indicate the first molecule has been created
                        }
                        else
                        {
                            if (base != 'X')
                                printf("Invalid nucleotide, enter again: ");
                        }
                    }
                    length++;

                    //adding this new molecule to the end of the molecule chain
                    /*NOTE: if a molecule placed earlier on in the chain is split,
                    the split molecule is inserted in the middle of the chain, thus
                    all the molecule ID's are shifted by one.*/
                    currentMolecule = firstMolecule;
                    for (int i = 1; i < length - 1; i++)
                    {
                        currentMolecule = currentMolecule->next;
                    }
                    newMolecule->next = currentMolecule->next;
                    currentMolecule->next = newMolecule;
                }
                else
                {
                    printf("ERROR: Invalid Chain ID.\n\n");
                    break;
                }
            }
            break;

        case 2:
            //case to insert a nucleotide in the chosen molecule at a specified position
            if (chain_status == 0) //checking if the chain exists
            {
                //choosing the molecule
                printf("Enter the ID of the molecule you want to insert into: ");
                scanf("%d", &molecule_ID);

                //traversing to the chosen molecule
                if (molecule_ID <= length)
                {
                    currentMolecule = firstMolecule;
                    for (int i = 1; i < molecule_ID; i++)
                    {
                        currentMolecule = currentMolecule->next;
                    }
                }
                else
                {
                    printf("ERROR: Cannot insert into a non-existent chain.\n\n");
                    break;
                }

                printf("Select the chain you want to add nucleotides to:\n1. Alpha\n2. Beta\nChoice: ");
                scanf("%d", &chain_ID);
                printf("Enter the nucleotide you want to insert (A, T, G, C): ");
                while ((base = getchar()) == '\n')
                    ;
                basePair = BasePair(base);
                if ((basePair != 'X'))
                {
                    printf("Enter position you want to insert at: ");
                    scanf("%d", &position);
                    //check for valid position
                    if ((position > 0) && ((position >= (currentMolecule->Alpha)->length + 1) || (position >= (currentMolecule->Beta)->length + 1)))
                    {
                        printf("ERROR: Cannot insert at given position.\n\n");
                    }

                    else if ((chain_ID == 1) || (chain_ID == 2))
                    {
                        Insert(chain_ID, base, position, currentMolecule);
                    }
                    else
                    {
                        printf("ERROR: Invalid Chain ID.\n\n");
                    }
                }
                else
                {
                    printf("ERROR: Invalid nucleotide.\n\n");
                }
            }
            else
            {
                printf("ERROR: Cannot insert into a non-existent chain.\n\n");
            }
            break;

        case 3:
            //case to delete a base pair in the chosen molecule from a specified position
            if (chain_status == 0) //checking if the chain exists
            {
                //choosing the molecule
                printf("Enter the ID of the molecule you want to delete from: ");
                scanf("%d", &molecule_ID);

                //travesing to the chosen molecule
                if (molecule_ID <= length)
                {
                    currentMolecule = firstMolecule;
                    for (int i = 1; i < molecule_ID; i++)
                    {
                        currentMolecule = currentMolecule->next;
                    }
                }
                else
                {
                    printf("ERROR: Cannot delete from a non-existent chain.\n\n");
                    break;
                }

                printf("Select the chain you want to delete nucleotides from:\n1. Alpha\n2. Beta\nChoice: ");
                scanf("%d", &chain_ID);
                printf("Enter position you want to delete: ");
                scanf("%d", &position);
                //check for valid position
                if ((position > 0) && ((position >= (currentMolecule->Alpha)->length + 1) || (position >= (currentMolecule->Beta)->length + 1)))
                {
                    printf("ERROR: Cannot insert at given position.\n\n");
                }
                else if ((chain_ID == 1) || (chain_ID == 2))
                {
                    Delete(currentMolecule, position);
                }
                else
                {
                    printf("ERROR: Invalid chain ID.\n\n");
                }
            }
            else
            {
                printf("ERROR: Cannot delete from a non-existent chain.\n\n");
            }
            break;

        case 4:
            //case to split a chosen molecule
            if (chain_status == 0) //checking if the chain exists
            {
                //choosing the molecule
                printf("Enter the ID of the molecule you want to split: ");
                scanf("%d", &molecule_ID);

                //traversing to the chosen molecule
                if (molecule_ID <= length)
                {
                    currentMolecule = firstMolecule;
                    for (int i = 1; i < molecule_ID; i++)
                    {
                        currentMolecule = currentMolecule->next;
                    }
                }
                else
                {
                    printf("ERROR: Cannot split a non-existent molecule.\n\n");
                    break;
                }
                printf("Slpitting the DNA molecule.\n\n");
                SplitChain(currentMolecule);
                length++; //number of molecules will increase by one when we split
            }
            else
            {
                printf("ERROR: Cannot split a non-existent molecule.\n\n");
            }
            break;

        case 5:
            //case to print a chosen DNA molecule
            if (chain_status == 0)
            {
                //choosing the molecule
                printf("Enter the ID of the molecule you want to display: ");
                scanf("%d", &molecule_ID);

                //traversing to the chosen molecule
                if (molecule_ID <= length)
                {
                    PrintChain(molecule_ID, firstMolecule, length);
                }
                else
                {
                    printf("ERROR: Cannot display a non-existent molecule.\n\n");
                    break;
                }
            }
            else
            {
                printf("ERROR: Cannot display a non-existent molecule.\n\n");
            }
            break;

        case 6:
            //case to print all the existing DNA molecules
            if ((chain_status == 0))
            {
                printf("Number of molecules: %d\n\n", length);
                PrintAllChains(firstMolecule, length);
            }
            else
                printf("ERROR: Cannot display a non-existent molecule.\n\n");
            break;

        case 7:
            //case to exit the menu loop
            printf("Bye!\n");
            break;

        default:
            //case to deal with invalid menu inputs
            printf("Invalid input! Enter again.\n\n");
        }
    } while (choice != 7);
}
