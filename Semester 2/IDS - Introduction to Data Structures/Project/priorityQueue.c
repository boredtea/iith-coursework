#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define POPULATION 10000 //mantains count of people, i.e., the population

struct event
{
    int day;     //stores the day on which the event occurs
    char status; //transmit (T) or recover (R)
    char person_ID;
};
typedef struct event Event;

Event priorityQueue[2 * POPULATION];
int heapSize = 0;
//priorityQueue[0] = -1;

Event createEvent(int ID, int day, char status, int neighbourID)
{
    Event newEvent;
    newEvent.person_ID = ID;
    newEvent.day = day;
    newEvent.status = status;
    //newEvent.neighbour_ID = neighbourID; //used when status is T

    return newEvent;
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

//function to see the maximum priority event, i.e., the minimum event
Event seeMinimum()
{
    return priorityQueue[1];
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
    else if (heapSize >= (2 * i))
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

//function to extract the highest priority event
Event extractEvent()
{
    Event extracted = priorityQueue[1];
    priorityQueue[1] = priorityQueue[heapSize]; //resetting the root as the last event in the queue
    heapSize--;                                 //reducing heap size
    percolateDown(1);

    return extracted;
}

void main()
{
    Event newEvent;
    newEvent = createEvent(1, 3, 'R', -1);
    addEvent(newEvent);
    newEvent = createEvent(1, 2, 'T', -1);
    addEvent(newEvent);
    newEvent = createEvent(5, 8, 'T', -1);
    addEvent(newEvent);
    newEvent = createEvent(6, 5, 'R', -1);
    addEvent(newEvent);
    newEvent = createEvent(7, 9, 'R', -1);
    addEvent(newEvent);
    newEvent = createEvent(7, 1, 'R', -1);
    addEvent(newEvent);

    for (int i = 1; i <= heapSize; i++)
        printf("%d \n", priorityQueue[i].day);

    Event current;
    while (heapSize >= 1)
    {
        current = extractEvent();
        printf("Day: %d \n", current.day);
        printf("Action: %c \n", current.status);
        printf("Person ID: %d \n", current.person_ID);
        printf("\n");

        //for (int i = 1; i <= heapSize; i++)
        //printf("%d \n", priorityQueue[i].day);
    }
}