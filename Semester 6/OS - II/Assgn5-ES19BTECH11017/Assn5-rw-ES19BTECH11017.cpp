#include <iostream>
#include <fstream>
#include <thread>
#include <sys/time.h>
#include <random>
#include <unistd.h>
#include <atomic>
#include <algorithm>
#include <semaphore.h>

using namespace std;

// input parameters
int nw, nr, kw, kr;
double avg_cs, avg_rem;

// semaphores
sem_t mutex, rw_mutex;

int read_count = 0;

// output file variables
FILE *log_file;

// random time for simulating processes
random_device seed;
default_random_engine generator;
// exponential distributions
exponential_distribution<double> cs, rem;

// time variables to print the time in the required format
tm *tempTime;
double ms;
struct timeval elapsed;

double currentTime;

// average and maximum waiting time variables
double writers_avgWaitingTime = 0;
double writers_maxWaitingTime = -1;

double readers_avgWaitingTime = 0;
double readers_maxWaitingTime = -1;

void writer(int id)
{
    generator.seed(42);
    time_t reqEnterTime, actEnterTime, exitTime;
    double elapsedTime;

    for (int i = 0; i < kw; i++)
    {
        reqEnterTime = time(NULL);
        tempTime = localtime(&reqEnterTime);
        gettimeofday(&elapsed, NULL);
        ms = elapsed.tv_usec / 1000.0;
        currentTime = 60000 * tempTime->tm_min + 1000 * tempTime->tm_sec + ms;

        fprintf(log_file, "%dth CS request by Writer Thread %d at %d:%d:%d:%d\n", i + 1, id, tempTime->tm_min, tempTime->tm_sec, int(ms), int(elapsed.tv_usec) - 1000 * int(ms));

        // entry section
        // writers code
        sem_wait(&rw_mutex); // increment

        actEnterTime = time(NULL);
        tempTime = localtime(&actEnterTime);
        gettimeofday(&elapsed, NULL);
        ms = elapsed.tv_usec / 1000.0;
        fprintf(log_file, "%dth CS entry by Writer Thread %d at %d:%d:%d:%d\n", i + 1, id, tempTime->tm_min, tempTime->tm_sec, int(ms), int(elapsed.tv_usec) - 1000 * int(ms));
        elapsedTime = 60000 * tempTime->tm_min + 1000 * tempTime->tm_sec + ms - currentTime;
        writers_avgWaitingTime += elapsedTime;
        writers_maxWaitingTime = max(elapsedTime, writers_maxWaitingTime);

        usleep(cs(generator) * 1000); // simulation of critical section
        sem_post(&rw_mutex);          // decrement

        // exit section
        exitTime = time(NULL);
        tempTime = localtime(&exitTime);
        gettimeofday(&elapsed, NULL);
        ms = elapsed.tv_usec / 1000.0;
        fprintf(log_file, "%dth CS exit by Writer Thread %d at %d:%d:%d:%d\n", i + 1, id, tempTime->tm_min, tempTime->tm_sec, int(ms), int(elapsed.tv_usec) - 1000 * int(ms));

        usleep(rem(generator) * 1000); // simulation of remainder section
    }
}

void reader(int id)
{
    generator.seed(42);
    time_t reqEnterTime, actEnterTime, exitTime;
    double elapsedTime;

    for (int i = 0; i < kw; i++)
    {
        reqEnterTime = time(NULL);
        tempTime = localtime(&reqEnterTime);
        gettimeofday(&elapsed, NULL);
        ms = elapsed.tv_usec / 1000.0;
        currentTime = 60000 * tempTime->tm_min + 1000 * tempTime->tm_sec + ms;

        fprintf(log_file, "%dth CS request by Reader Thread %d at %d:%d:%d:%d\n", i + 1, id, tempTime->tm_min, tempTime->tm_sec, int(ms), int(elapsed.tv_usec) - 1000 * int(ms));

        // entry section
        // writers code
        sem_wait(&mutex); // increment
        read_count++;
        if (read_count == 1)
            sem_wait(&rw_mutex); // increment
        sem_post(&mutex);        // decrement

        actEnterTime = time(NULL);
        tempTime = localtime(&actEnterTime);
        gettimeofday(&elapsed, NULL);
        ms = elapsed.tv_usec / 1000.0;
        fprintf(log_file, "%dth CS entry by Reader Thread %d at %d:%d:%d:%d\n", i + 1, id, tempTime->tm_min, tempTime->tm_sec, int(ms), int(elapsed.tv_usec) - 1000 * int(ms));
        elapsedTime = 60000 * tempTime->tm_min + 1000 * tempTime->tm_sec + ms - currentTime;
        readers_avgWaitingTime += elapsedTime;
        readers_maxWaitingTime = max(elapsedTime, readers_maxWaitingTime);

        usleep(cs(generator) * 1000); // simulation of critical section

        sem_wait(&mutex); // increment
        read_count--;
        if (read_count == 0)
            sem_post(&rw_mutex); // decrement
        sem_post(&mutex);        // decrement

        // exit section
        exitTime = time(NULL);
        tempTime = localtime(&exitTime);
        gettimeofday(&elapsed, NULL);
        ms = elapsed.tv_usec / 1000.0;
        fprintf(log_file, "%dth CS exit by Reader Thread %d at %d:%d:%d:%d\n", i + 1, id, tempTime->tm_min, tempTime->tm_sec, int(ms), int(elapsed.tv_usec) - 1000 * int(ms));

        usleep(rem(generator) * 1000); // simulation of remainder section
    }
}

int main()
{
    // random time variables
    cs = exponential_distribution<double>(1.0 / avg_cs);
    rem = exponential_distribution<double>(1.0 / avg_rem);

    // read input params
    ifstream input_file;
    input_file.open("inp-params.txt", ios::in);
    input_file >> nw >> nr >> kw >> kr >> avg_cs >> avg_rem;
    input_file.close();

    // open log file
    log_file = fopen("RW-log.txt", "w");
    // set semaphores to 1
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    thread writerThreads[nw];
    thread readerThreads[nr];

    for (int i = 0; i < nw; i++)
        writerThreads[i] = thread(writer, i + 1);
    for (int i = 0; i < nr; i++)
        readerThreads[i] = thread(reader, i + 1);

    for (int i = 0; i < nw; i++)
        writerThreads[i].join();
    for (int i = 0; i < nr; i++)
        readerThreads[i].join();

    pclose(log_file);

    ofstream fout;
    fout.open("Average_time.txt", ofstream::app);
    double avgWaitingTime = (readers_avgWaitingTime + writers_avgWaitingTime) / double(nr * kr + nw * kw);
    fout << "Average waiting time (RW): " << avgWaitingTime << " ms" << endl;
    fout.close();

    cout << "Average time taken by a writer thread to enter the CS: " << writers_avgWaitingTime / double(nw * kw) << " ms" << endl;
    cout << "Average time taken by a reader thread to enter the CS: " << readers_avgWaitingTime / double(nr * kr) << " ms" << endl;

    cout << "Worst case time taken by a writer thread to enter the CS: " << writers_maxWaitingTime << " ms" << endl;
    cout << "Worst case time taken by a reader thread to enter the CS: " << readers_maxWaitingTime << " ms" << endl;

    return 0;
}