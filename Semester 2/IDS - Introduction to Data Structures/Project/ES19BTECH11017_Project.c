#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define POPULATION 10000 //mantains count of people, i.e., the population
#define MAX_DAYS 300     //the maximum number of days up to which we need to keep assessing the priority queue
#define MAX_EDGES 10  //the maximum number of neighbours a person can have
#define Tau 0.5
#define Gamma 0.2

int S = POPULATION, I = 0, R = 0; //variables to keep count of S, I and R people

int adjacencyMatrix[POPULATION][POPULATION];

//structure to maintain information about each person
struct person
{
    int ID;              //between 0 to POPULATION - 1
    char status;         // S, I or R
    int minInfectionDay; //used to keep track of the earliest on which a person will be infected
    int neighbours;      //keeps count of the number of neighbours each person has
};
typedef struct person Person;

//array to maintain a list of every person in the population
Person people[POPULATION]; 

//structure to store an event during the pandemic
struct event
{
    int day;     //stores the day on which the event occurs
    char status; //transmit (T) or recover (R)
    Person person_ID;
    int neighbour_ID; //if the status is T, then this stores the neighbour it has to transmit to
};
typedef struct event Event;

//function to create and return a new event
Event createEvent(int ID, int day, char status, int neighbourID)
{
    Event newEvent;
    newEvent.person_ID.ID = ID;
    newEvent.day = day;
    newEvent.status = status;
    newEvent.neighbour_ID = neighbourID; //used when status is T, otherwise -1

    return newEvent;
}

//declaring priority queue variables
Event priorityQueue[10 * POPULATION];
int heapSize = 0;

//function to return either 0 or 1 to help fill the adjacency matrix
int neighbours()
{
    int n = rand() % 2;
    return n;
}

//functions to generate the adjacency matrix and fill up the people array
void generateNeighbours()
{
    int new;
    int neighbourTotal = 0;
    for (int i = 0; i < POPULATION; i++)
    {
        for (int j = i + 1; j < POPULATION; j++)
        {
            //filling up the people array
            if (i == 0)
            {
                people[j].ID = j;
                people[j].status = 'S';               //initially, everyone is susceptible
                people[j].neighbours = 0;             //initially, everyone has 0 neighbours
                people[j].minInfectionDay = MAX_DAYS; //initially, person doesn't have any infection day, so setting it to max
            }
            if (i == j)
                adjacencyMatrix[j][j] = 0; //a person can't be their own neighbour
            else
            {
                new = neighbours();
                if (new == 1 && people[i].neighbours <= MAX_EDGES && people[j].neighbours <= MAX_EDGES)
                {
                    adjacencyMatrix[i][j] = new;
                    adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
                    //keeping track of the number of neighbours
                    people[i].neighbours++;
                    people[j].neighbours++;
                    neighbourTotal++;
                }
                else
                {
                    adjacencyMatrix[i][j] = 0;
                    adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
                }
            }
        }
    }
}

//function to return a recovery day for an infected person
int getRecoveryTime(double gamma, int infectionDay)
{
    int day = infectionDay + 1;
    int heads = 0;
    double coin;

    while (heads == 0)
    {
        /*
        Generates numbers between 1 to 10.
        If the value of coin is lesser than 10 * gamma, 
        the coin is heads up. Else, it's tails up.
        */
        coin = rand() % 100 + 1; //tossing the coin

        if (coin <= (100 * gamma))
            heads = 1;
        else
            day++;
    }
    return day;
}

//function to return a transmission day for an infected person's neighbour
int getTransmissionTime(double tau, int infectionDay)
{
    int day = infectionDay + 1;
    int heads = 0;
    double coin;

    while (heads == 0)
    {
        /*
        Generates numbers between 1 to 10.
        If the value of coin is lesser than 10 * tau, 
        the coin is heads up. Else, it's tails up.
        */
        coin = rand() % 100 + 1; //tossing the coin

        if (coin <= (100 * tau))
            heads = 1;
        else
            day++;
    }
    return day;
}

//function to swap two events in the priority queue
void swap(int a, int b)
{
    Event temp;
    temp = priorityQueue[a];
    priorityQueue[a] = priorityQueue[b];
    priorityQueue[b] = temp;
}

//function to place an event in it's right position in the heap while adding
void bubbleUp(int i)
{
    if (priorityQueue[i / 2].day > priorityQueue[i].day)
    {
        swap(i, i / 2);
        bubbleUp(i / 2);
    }
}

//function to add an event to the priority queue
void addEvent(Event newEvent)
{
    heapSize++;
    int i = heapSize;
    priorityQueue[i] = newEvent;
    bubbleUp(i); //finding the correct position of the new event in the heap
}


//function to return the index of the minimum valued child of a parent
int findMinChild(int i)
{
    int index = -1;
    if (heapSize >= (2 * i) && heapSize >= (2 * i + 1))
    {
        if (priorityQueue[2 * i].day < priorityQueue[2 * i + 1].day)
            index = 2 * i;
        else
            index = (2 * i) + 1;
    }
    else if (heapSize >= (2 * i)) //only one child case
    {
        if (priorityQueue[2 * i].day < priorityQueue[i].day)
            index = 2 * i;
    }
    return index;
}

//function to place an event in it's right position in the heap while removing root
void percolateDown(int i)
{
    int minIndex = findMinChild(i);
    if (minIndex != -1 && priorityQueue[i].day > priorityQueue[minIndex].day)
    {
        swap(i, minIndex);
        percolateDown(minIndex);
    }
}

//function to extract the highest priority event from the priority queue
Event extractEvent()
{
    Event extracted = priorityQueue[1];
    priorityQueue[1] = priorityQueue[heapSize]; //resetting the root as the last event in the queue
    heapSize--;                                 //reducing heap size
    percolateDown(1);

    return extracted;
}

//function to start the pandemic
void startPandemic(int startPoints)
{
    int index;
    int recoverDay, transmitDay;
    for (int j = 1; j <= startPoints; j++)
    {
        index = rand() % POPULATION;
        people[index].status = 'I';
        S--;
        I++;

        //recovery day
        recoverDay = getRecoveryTime(Gamma, 0);

        //creating and adding new events to the priority queue

        Event newEvent;
        //transmission to the neighbours of the infected person 
        for (int i = 0; i < POPULATION; i++)
        {
            if (adjacencyMatrix[i][people[index].ID] == 1)
            {
                if (people[i].status == 'S')
                {
                    //transmission day
                    transmitDay = getTransmissionTime(Tau, 0);
                    //checking for valid/duplicate transmission days for a person
                    if (transmitDay < people[i].minInfectionDay && transmitDay < recoverDay)
                    {
                        people[i].minInfectionDay = transmitDay;
                        newEvent = createEvent(people[index].ID, transmitDay, 'T', i);
                        addEvent(newEvent);
                    }
                }
            }
        }
        //adding the recovery event
        newEvent = createEvent(people[index].ID, recoverDay, 'R', -1);
        addEvent(newEvent);
    }
}

//function to propogate and transmit the pandemic 
int transmit(int day, int person_ID)
{
    int recoverDay, transmitDay;

    people[person_ID].status = 'I';
    
    Event newEvent;

    //adding the recovery event for the current person
    recoverDay = getRecoveryTime(Gamma, day);
    if (recoverDay <= MAX_DAYS)
    {
        newEvent = createEvent(person_ID, recoverDay, 'R', -1);
        addEvent(newEvent);
    }

    //transmitting to the neighbours of the current person
    for (int i = 0; i < POPULATION; i++)
    {
        if (adjacencyMatrix[i][people[person_ID].ID] == 1)
        {
            if (people[i].status == 'S')
            {
                transmitDay = getTransmissionTime(Tau, day);
                //checking for valid/duplicate transmission days for a person
                if (transmitDay < recoverDay && transmitDay <= MAX_DAYS)
                {
                    if (transmitDay < people[i].minInfectionDay)
                    {
                        people[i].minInfectionDay = transmitDay;
                        newEvent = createEvent(person_ID, transmitDay, 'T', i);
                        addEvent(newEvent);
                    }
                }
            }
        }
    }
}

void main()
{
    //seeding for all the random generators in the program
    srand(time(NULL));

    //generating the adjacency matrix
    generateNeighbours();

    //starting the pandemic
    startPandemic(5);
    int day = 0;

    Event current;

    //printing initial status
    printf("Day 0:\n");
    printf("S: %d   I: %d   R: %d\n", S, I, R);
    printf("==================================\n");

    //dequeuing from the priority queue until there are no events remaining
    while (heapSize >= 1)
    {
        current = extractEvent();

        //printing status every time the day changes
        if (day != current.day)
        {
            printf("Day %d: \n", current.day);
            printf("S: %d   I: %d   R: %d\n", S, I, R);
            printf("==================================\n");
            day = current.day;
        }

        if (current.status == 'R') //recovery
        {
            people[current.person_ID.ID].status = 'R';
            I--;
            R++;
        }
        else if (current.status == 'T') //transmission
        {
            //transmitting virus to the neighbours of the current person
            if (people[current.neighbour_ID].status == 'S' && people[current.neighbour_ID].minInfectionDay >= current.day)
            {
                S--;
                I++;
                transmit(current.day, current.neighbour_ID);
            }
        }
    }

    //printing final status
    printf("Day %d: \n", current.day);
    printf("S: %d   I: %d   R: %d\n", S, I, R);
    printf("==================================\n");
}
