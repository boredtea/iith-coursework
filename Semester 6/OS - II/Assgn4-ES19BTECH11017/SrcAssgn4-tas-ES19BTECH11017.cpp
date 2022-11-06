#include <iostream>
#include <fstream>
#include <thread>
#include <sys/time.h>
#include <random>
#include <unistd.h>
#include <atomic>
#include <algorithm>

using namespace std;

// input parameters
int n, k, lambda1, lambda2;

// atomic lock variable
atomic_flag lock = ATOMIC_FLAG_INIT;

// output file variables
ofstream log_file;

// time variables to print the time in the required format
tm *tempTime;
double ms;
struct timeval elapsed;

double currentTime;

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

    for (int i = 0; i < k; i++)
    {
        reqEnterTime = time(NULL);
        tempTime = localtime(&reqEnterTime);
        gettimeofday(&elapsed, NULL);
        ms = elapsed.tv_usec / 1000.0;
        currentTime = 60000 * tempTime->tm_min + 1000 * tempTime->tm_sec + ms;

        log_file << i + 1 << "th CS Request at " << tempTime->tm_min << ":" << tempTime->tm_sec << " by thread " << id << endl;

        // entry section
        // critical section implementation (TAS)
        while (lock.test_and_set());

        actEnterTime = time(NULL);
        tempTime = localtime(&actEnterTime);
        gettimeofday(&elapsed, NULL);
        ms = elapsed.tv_usec / 1000.0;
        log_file << i + 1 << "th CS Entry at " << tempTime->tm_min << ":" << tempTime->tm_sec << " by thread " << id << endl;

        elapsedTime = 60000 * tempTime->tm_min + 1000 * tempTime->tm_sec + ms - currentTime;
        avgWaitingTime += elapsedTime;
        maxWaitingTime = max(elapsedTime, maxWaitingTime);
        
        usleep(t1(generator) * 1000); // simulation of critical section

        // exit section
        //  set lock back to false
        lock.clear();

        exitTime = time(NULL);
        tempTime = localtime(&exitTime);
        log_file << i + 1 << "th CS Exit at " << tempTime->tm_min << ":" << tempTime->tm_sec << " by thread " << id << endl;

        usleep(t2(generator) * 1000); // simulation of remainder section
    }
}

int main()
{
    // int n, k, lambda1, lambda2;
    ifstream input_file;
    input_file.open("inp-params.txt", ios::in);
    input_file >> n >> k >> lambda1 >> lambda2;
    input_file.close();

    // open log file
    log_file.open("TAS-log.txt", ios::out | ofstream::app);

    thread threads[n];

    for (int i = 0; i < n; i++)
        threads[i] = thread(testCS, i + 1);
    for (int i = 0; i < n; i++)
        threads[i].join();

    log_file.close();

    avgWaitingTime = avgWaitingTime / double(n * k);
    maxWaitingTime = maxWaitingTime;
    cout << "Average time taken by a process to enter the CS: " << avgWaitingTime << " ms" << endl;
    cout << "Worst case time taken by a process to enter the CS: " << maxWaitingTime << " ms" << endl;

    return 0;
}