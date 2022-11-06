#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// struct to store details about each process
struct Process
{
    int p_id;            // process ID
    int t;               // process time
    int period;          //period
    int k;               //number of time each process repeats
    double priority;     //reciprocal of period
    double waiting_time; //stores the average waiting time of all the instances of one process
};

struct ProcessDetails
{
    int p_id;
    int t;
    int period;
    double priority;
    int arrival_time;
    int deadline;
    int remaining_time;
    int completion_status; // -1 = never scheduled, 0 = scheduled but not finished, 1 = scheduled and finished
    int index;             // index in processesList
    int waiting_time;
};

// fuction to sort processes by arrival times and priorities
bool sortProcess(const ProcessDetails &P1, const ProcessDetails &P2)
{
    if (P1.arrival_time == P2.arrival_time)
        return P1.priority >= P2.priority;
    else
        return P1.arrival_time < P2.arrival_time;
}

// comparison struct for declaring the ready queue
struct queueCompare
{
    bool operator()(const ProcessDetails &P1, const ProcessDetails &P2)
    {
        if (P1.priority != P2.priority)
            return P1.priority < P2.priority;
        else
            return P1.arrival_time < P2.arrival_time;
    }
};

// vector to store every individual process as a separate process
vector<ProcessDetails> processList;
// ready queue
priority_queue<ProcessDetails, vector<ProcessDetails>, queueCompare> readyQueue;
// queue to store preempted processes
queue<ProcessDetails> preemptedList;

int current_time = 0, current_arrival_time = 0;

// function to schedule the process
void EDFscheduler()
{
    ofstream output_file;
    output_file.open("EDF-Log.txt", ios::app);

    int topProcess = 0;
    int deadline_flag = 1;

    ProcessDetails currentP;
    current_time = processList[0].arrival_time;
    while (topProcess < processList.size() || readyQueue.size() != 0)
    {
        current_arrival_time = processList[topProcess].arrival_time;

        // adding all processes with the same arrival time into the ready queue
        while (topProcess < processList.size() && processList[topProcess].arrival_time <= current_arrival_time)
        {
            readyQueue.push(processList[topProcess]);
            topProcess++;
        }

        // adding preempted processes back to the ready queue
        while (preemptedList.size() != 0)
        {
            readyQueue.push(preemptedList.front());
            preemptedList.pop();
        }

        // processing the ready queue
        while (!readyQueue.empty())
        {
            currentP = readyQueue.top();
            readyQueue.pop();

            // case where there is no chance of preemption
            if (current_time + currentP.remaining_time <= processList[topProcess].arrival_time)
            {
                // if process will be able to meet deadline
                if (current_time + currentP.remaining_time <= currentP.deadline)
                {
                    // log start of execution
                    if (currentP.completion_status == -1)
                    {
                        output_file << "Process P" << currentP.p_id << " starts execution at time " << current_time << "." << endl;
                        currentP.completion_status = 0;
                    }
                    else if (currentP.completion_status == 0)
                    {
                        output_file << "Process P" << currentP.p_id << " resumes execution at time " << current_time << "." << endl;
                    }

                    current_time = current_time + currentP.remaining_time;
                    output_file << "Process P" << currentP.p_id << " finishes execution at time " << current_time << "." << endl;
                    // mark process as completed
                    currentP.completion_status = 1; // mark process as completed
                    processList[currentP.index].completion_status = 1;
                    currentP.remaining_time = 0;
                    processList[currentP.index].remaining_time = 0;

                    // update waiting time
                    processList[currentP.index].waiting_time = current_time - currentP.arrival_time - currentP.t;
                }
                else
                {
                    // log start of execution
                    if (currentP.completion_status == -1)
                    {
                        output_file << "Process P" << currentP.p_id << " starts execution at time " << current_time << "." << endl;
                        currentP.completion_status = 0;
                    }
                    else if (currentP.completion_status == 0)
                    {
                        output_file << "Process P" << currentP.p_id << " resumes execution at time " << current_time << "." << endl;
                    }

                    // update current time
                    current_time = current_time > currentP.deadline ? current_time : currentP.deadline;

                    output_file << "Terminated. Process P" << currentP.p_id << " couldn't meet its deadline at time " << currentP.deadline << "." << endl;
                    deadline_flag = 0;
                    processList[currentP.index].waiting_time = currentP.deadline - currentP.arrival_time - (currentP.t - currentP.remaining_time);
                }
            }
            // case where there is a possibility of preemption but the ready queue process has higher priority
            else if (currentP.priority >= processList[topProcess].priority)
            {
                // if process will be able to meet deadline
                if (current_time + currentP.remaining_time <= currentP.deadline)
                {
                    // log start of execution
                    if (currentP.completion_status == -1)
                    {
                        output_file << "Process P" << currentP.p_id << " starts execution at time " << current_time << "." << endl;
                        currentP.completion_status = 0;
                    }
                    else if (currentP.completion_status == 0)
                    {
                        output_file << "Process P" << currentP.p_id << " resumes execution at time " << current_time << "." << endl;
                    }

                    current_time = current_time + currentP.remaining_time;
                    output_file << "Process P" << currentP.p_id << " finishes execution at time " << current_time << "." << endl;

                    // mark process as completed
                    currentP.completion_status = 1; // mark process as completed
                    processList[currentP.index].completion_status = 1;
                    currentP.remaining_time = 0;
                    processList[currentP.index].remaining_time = 0;

                    // update waiting time
                    processList[currentP.index].waiting_time = current_time - currentP.arrival_time - currentP.t;
                }
                else
                {
                    // log start of execution
                    if (currentP.completion_status == -1)
                    {
                        output_file << "Process P" << currentP.p_id << " starts execution at time " << current_time << "." << endl;
                        currentP.completion_status = 0;
                    }
                    else if (currentP.completion_status == 0)
                    {
                        output_file << "Process P" << currentP.p_id << " resumes execution at time " << current_time << "." << endl;
                    }

                    // update current time
                    current_time = current_time > currentP.deadline ? current_time : currentP.deadline;

                    output_file << "Terminated. Process P" << currentP.p_id << " couldn't meet its deadline at time " << currentP.deadline << "." << endl;
                    deadline_flag = 0;
                    processList[currentP.index].waiting_time = currentP.deadline - currentP.arrival_time - (currentP.t - currentP.remaining_time);
                }
            }
            else // preempt
            {    // log only if the process gets to execute at all to begin with
                if ((processList[topProcess].arrival_time - current_time) > 0)
                {
                    // log start of execution
                    if (currentP.completion_status == -1)
                    {
                        output_file << "Process P" << currentP.p_id << " starts execution at time " << current_time << "." << endl;
                        currentP.completion_status = 0;
                    }
                    else if (currentP.completion_status == 0)
                    {
                        output_file << "Process P" << currentP.p_id << " resumes execution at time " << current_time << "." << endl;
                    }

                    currentP.remaining_time = currentP.remaining_time - (processList[topProcess].arrival_time - current_time);
                    current_time = current_time > processList[topProcess].arrival_time ? current_time : processList[topProcess].arrival_time;

                    output_file << "Process P" << currentP.p_id << " is preempted by Process P" << processList[topProcess].p_id << " at time " << current_time
                                << ". Remaining processing time:" << currentP.remaining_time << endl;
                }
                preemptedList.push(currentP);
            }

            if (readyQueue.empty() && preemptedList.empty() && topProcess != processList.size())
            {
                if (current_time < processList[topProcess].arrival_time)
                {
                    output_file << "CPU is idle till time " << processList[topProcess].arrival_time << "." << endl;
                    current_time = processList[topProcess].arrival_time;
                }
            }
        }
    }
    output_file.close();
}

int main()
{
    int n, k, total_processes = 0;

    ifstream input_params;
    input_params.open("inp-params.txt", ios::in);
    input_params >> n;

    // array to store details of each unique process
    Process processes[n];

    ofstream output_file;
    output_file.open("EDF-Log.txt", ios::out);

    //Read all the process details from input file
    for (int i = 0; i < n; i++)
    {
        input_params >> processes[i].p_id;
        input_params >> processes[i].t;
        input_params >> processes[i].period;
        input_params >> processes[i].k;
        processes[i].priority = 1 / double(processes[i].period);
        processes[i].waiting_time = 0;

        total_processes += processes[i].k;

        k = processes[i].k;

        // writing details about each process to the top of the log file
        output_file << "Process P" << processes[i].p_id << ": processing time=" << processes[i].t << "; deadline:" << processes[i].period << "; period:" << processes[i].period << " joined the system at time 0" << endl;

        // adding all the repeated processes as individual processes to the process list
        for (int j = 0; j < processes[i].k; j++)
        {
            ProcessDetails newProcess;
            newProcess.p_id = processes[i].p_id;
            newProcess.t = processes[i].t;
            newProcess.period = processes[i].period;
            newProcess.arrival_time = j * processes[i].period;
            newProcess.deadline = newProcess.arrival_time + newProcess.period;
            newProcess.priority = 1.0 / double(newProcess.deadline);
            newProcess.remaining_time = processes[i].t;
            newProcess.completion_status = -1;
            newProcess.waiting_time = 0;
            processList.push_back(newProcess);
        }
    }

    // sort priority list
    sort(processList.begin(), processList.end(), sortProcess);
    // assigning indices to each process
    for (int i = 0; i < processList.size(); i++)
    {
        processList[i].index = i;
    }

    output_file.close();

    EDFscheduler();

    // computing stats and writing them to the file
    int completed = 0, missed = 0;
    double avg_waiting_time = 0;
    for (int i = 0; i < processList.size(); i++)
    {
        if (processList[i].completion_status == 1)
        {
            completed++;
        }
        processes[processList[i].p_id - 1].waiting_time += processList[i].waiting_time;
        avg_waiting_time += processList[i].waiting_time;
    }
    missed = processList.size() - completed;
    avg_waiting_time = avg_waiting_time / double(total_processes);

    output_file.open("EDF-Stats.txt", ios::out);
    output_file << "Number of processes that came into the system: " << processList.size() << endl;
    output_file << "Number of processes that successfully completed: " << completed << endl;
    output_file << "Number of processes that missed their deadlines: " << missed << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     processes[i].waiting_time /= double(processes[i].k);
    //     output_file << "Average waiting time for Process P" << processes[i].p_id << ": " << processes[i].waiting_time << " milliseconds" << endl;
    // }
    output_file << "Average waiting time for all processes: " << avg_waiting_time << " milliseconds" << endl;

    output_file.close();

    return 0;
}