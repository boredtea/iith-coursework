#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/**********STRUCTURES**********/

/*NODE
The node struct helps in making individual units of the queue.
One node consists of the job number and the time required (in microseconds)
for the job, and a pointer to point to the next unit.
*/
struct node
{
    int jobNumber;
    int time;
    int timeReceived; //ensures a job gets a full quantum of processing time when required
    struct node *next;
};
typedef struct node Node;


/*QUEUE
The queue struct helps in making building a functioning queue.
It links the nodes together and keeps track of the length of the queue.
*/
struct queue
{
    Node *start;
    Node *end;
    int length; //stores length of the queue and helps with indentation while printing
};
typedef struct queue Queue;


/**********FUNCTIONS**********/

/*
Function to allocate space in memory to the queue and 
return a pointer to the new, empty queue
*/
Queue *createQueue()
{
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->length = 0;
    Node *fakeStart = (Node *)malloc(sizeof(Node));
    fakeStart->next = NULL;
    Q->start = fakeStart;
    Q->end = fakeStart;
    return Q;
}


/*
Function to add new job to the queue.
*/
void InsertEnd(Queue *Q, int jobNumber, int time)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->jobNumber = jobNumber;
    newnode->time = time;
    newnode->timeReceived = 0;
    newnode->next = NULL;

    //inserting in the end
    Node *current;

    if(Q->length == 0)
    {
        current = Q->start;
        newnode->next = current->next;
        current->next = newnode;
        Q->end = newnode;
    }
    else
    {
        current = Q->end;
        newnode->next = current->next;
        current->next = newnode;
        Q->end = newnode;
    }
    
    Q->length++; //incrementing length of the queue
}

/*
Function to pop a node from a stack.
*/
void DeleteBeginning(Queue *Q)
{
    //deleting from the beginning
    Node *current = Q->start;
    if(Q->length == 1)
        Q->end = current;
    else
    {
        Node *helper = current->next;
        current->next = helper->next;
    }
    Q->length--; //decrementing length of the queue
}


/*
Function to print the current queue with the proper indentation.
*/
void Print(Queue *Q, int time)
{
    Node *current = Q->start;
    printf("Queue at end of %d microseconds: \n", time);
    for(int i = 0; i < Q->length - 1; i++)
    {
        current = current->next;
        printf("J%d:%d, ", current->jobNumber, current->time);
    }
    current = current->next;
    printf("J%d:%d\n\n", current->jobNumber, current->time);
    
}


/*
Function to add new jobs to the queue after every 200 microseconds. 
*/
void appendNewJobs(Queue *Q, int queueStatus, int append)
{
    int startingJobNumber = 10; //helps in figuring out the first job number in the queue to be appended
    for(int i = 1; i < queueStatus; i++)
    {
        startingJobNumber = startingJobNumber + pow(2, append - i);
    }
    //appending 2^(append - queueStatus) jobs to the existing list until queueStatus == 1
    int jobTime;
    srand(time(0)); //seeding
    for(int i = 0; i < pow(2, append - queueStatus); i++)
    {
        jobTime = (rand() % 300); //generating random numbers between 0 and 300

        InsertEnd(Q, ++startingJobNumber, jobTime);
    }

}


void completeJobs(Queue *Q)
{
    Node *current = Q->start->next;

    
    //used to keep track of the time remaining in the cycle
    int timeRemaining = 50;
    int remove;
    int timeLastCycle = 0;
    while(timeRemaining > 0 && Q->length != 0)
    {
        current = Q->start->next;
        if(current->time <= timeRemaining)
        {
            //remove = ((50 - current->timeReceived) < timeRemaining) ? (50 - current->timeReceived) : timeRemaining;
            if(current->timeReceived == 0)
            {
                timeRemaining = timeRemaining - current->time;
                current->timeReceived = current->timeReceived + current->time;
                current->time = 0;
                DeleteBeginning(Q);
            }
            else
            {
                //picks and removes the minimum between current->time and 50 - current->timeReceived to ensure a 
                //task doesn't get more than 50 us in one cycle
                int toGive = (current->time <= 50 - current->timeReceived) ? current->time : (50 - current->timeReceived);

                current->time = current->time - toGive;
                timeRemaining = timeRemaining - toGive;
                current->timeReceived = 0;

                DeleteBeginning(Q);
                InsertEnd(Q, current->jobNumber, current->time);
            }
            
        }
        else
        {
            if(current->timeReceived == 0)
            {
                current->time = current->time - timeRemaining;
                current->timeReceived = current->timeReceived + timeRemaining;

                //de-queueing only if the job got a full 50 microseconds
                if(timeRemaining == 50)
                {
                    DeleteBeginning(Q);
                    InsertEnd(Q, current->jobNumber, current->time);
                }

                timeRemaining = 0;
            }
            else
            {
                current->time = current->time - (50 - current->timeReceived);
                timeRemaining = timeRemaining - (50 - current->timeReceived);
                current->timeReceived = 0;

                DeleteBeginning(Q);
                InsertEnd(Q, current->jobNumber, current->time);
            }
            
        }
    }   
}


/*
Main function.
*/
int main()
{
    Queue *Q = createQueue(); //allocating memory to Queue object Q using createQueue()
    int job, jobTime;
    int totalNewJobs = 0; //keeps track of total number of jobs after the first 100

    //creating first 100 jobs
    srand(time(0)); //seeding
    while(Q->length < 10)
    {
        jobTime = (rand() % 300); //generating random numbers between 0 and 300

        InsertEnd(Q, Q->length + 1, jobTime);
    }

    //keeps track of how many sets of 50 microseconds have passed AND
    //used to keep track of the number of times new jobs have been appended to the original queue
    //new jobs will be appended a total of 7 times, starting from 64 jobs, to 32 jobs and so on time 1 job
    //thus, when (timeFlag * 50) is a product of 200, the first time 64 jobs will be appended, 
    //then 32 jobs, and so on and so forth

    int timeFlag = 0; 
    int append = 4; //keeps track of how many queues to append
    while(Q->length > 0)
    {
        completeJobs(Q);
        timeFlag++;
        if((((timeFlag * 50) % 200) == 0) && ((timeFlag * 50) / 200) <= append)
        {
            appendNewJobs(Q, (timeFlag * 50) / 200, append);
            //appendNewJobs(Q, timeFlag * 50) / 200, append);
            printf("********* %d microseconds passed: added %d new job(s) at the end of queue\n", timeFlag * 50, (int)pow(2, append - (timeFlag * 50) / 200));
        }
        Print(Q, timeFlag * 50);
    }
}
