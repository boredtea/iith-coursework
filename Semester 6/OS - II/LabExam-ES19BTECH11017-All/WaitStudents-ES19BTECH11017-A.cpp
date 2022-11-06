#include <iostream>
#include <fstream>
#include <thread>
#include <sys/time.h>
#include <random>
#include <unistd.h>
#include <atomic>
#include <algorithm>
#include <queue>

using namespace std;

// input parameters
// int n, k, lambda1, lambda2;

int K, m, n;
double lambda1, lambda2;
int occupied_count = 0;

// atomic lock variable
atomic<bool> lock(false);

// output file variables
ofstream log_file;

// time variables to print the time in the required format
tm *tempTime;
double ms;
struct timeval elapsed;

double currentTime;

// semaphores
sem_t mutex, empty, full;

// average and maximum waiting time variables
double avgWaitingTime = 0;
double maxWaitingTime = -1;

void testCS(int id)
{
    time_t reqEnterTime, actEnterTime, exitTime;
    double elapsedTime;

    // random variable seed
    random_device seed;
    default_random_engine generator(seed());
    // exponential distributions
    exponential_distribution<double> t1(lambda1); // critical section time
    exponential_distribution<double> t2(lambda2); // remainder section time

    // since each student can take each subject with 1/K probability, assuming each student needs to request the lab K times, once for each subject
    for (int i = 0; i < K; i++)
    {
        reqEnterTime = time(NULL);
        tempTime = localtime(&reqEnterTime);
        gettimeofday(&elapsed, NULL);
        ms = elapsed.tv_usec / 1000.0;
        currentTime = 60000 * tempTime->tm_min + 1000 * tempTime->tm_sec + ms;

        log_file << "Student " << i + 1 << " of subject k" << id << " requested the lab at " << tempTime->tm_min << ":" << tempTime->tm_sec << endl;

        // entry section
        //  critical section implementation (CAS)
        bool expected = false;
        while (!atomic_compare_exchange_strong(&lock, &expected, true))
            expected = false;

        actEnterTime = time(NULL);
        tempTime = localtime(&actEnterTime);
        gettimeofday(&elapsed, NULL);
        ms = elapsed.tv_usec / 1000.0;
        log_file << "Student " << i + 1 << " of subject k" << id << " entered the lab at " << tempTime->tm_min << ":" << tempTime->tm_sec << endl;

        elapsedTime = 60000 * tempTime->tm_min + 1000 * tempTime->tm_sec + ms - currentTime;
        avgWaitingTime += elapsedTime;
        maxWaitingTime = max(elapsedTime, maxWaitingTime);
        
        usleep(t1(generator) * 1000); // simulation of critical section

        // exit section
        //  set lock back to false
        lock = false;

        exitTime = time(NULL);
        tempTime = localtime(&exitTime);
        log_file << "Student " << i + 1 << " of subject k" << id << " exited the lab at " << tempTime->tm_min << ":" << tempTime->tm_sec << " by thread " << id << endl;

        usleep(t2(generator) * 1000); // simulation of remainder section
    }
}

int main()
{
    // int n, k, lambda1, lambda2;
    ifstream input_file;
    input_file.open("inp-params.txt", ios::in);
    // input_file >> n >> k >> lambda1 >> lambda2;
    input_file >> K >> m >> lambda1 >> n >> lambda2;
    

    input_file.close();

    // open log file
    log_file.open("LogFile-ES19BTECH11017-A.txt", ios::out | ofstream::app);

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, m);
    sem_init(&full, 0, 0);


    thread threads[n];

    for (int i = 0; i < n; i++)
        threads[i] = thread(testCS, i + 1);
    for (int i = 0; i < n; i++)
        threads[i].join();

    log_file.close();

    avgWaitingTime = avgWaitingTime / double(n * K);
    maxWaitingTime = maxWaitingTime;
    cout << "Average time taken by a student to enter the lab: " << avgWaitingTime << " ms" << endl;
    // cout << "Worst case time taken by a process to enter the CS: " << maxWaitingTime << " ms" << endl;

    return 0;
}