#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/wait.h>

struct start_times
{
    double seconds;
    double microseconds;
};

int main(int argc, char *argv[])
{
    /* name of the shared memory object */
    const char *name = "OS-ASS-1";

    /* the size (in bytes) of shared memory object */
    const int SIZE = 4096;

    /* pointer to shared memory obect */
    struct start_times *ptr;

    /* declaring variables required for checking the time */
    double elapsed_time;
    struct timeval current;

    /* create the shared memory object */
    int FD = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* configure the size of the shared memory object */
    ftruncate(FD, SIZE);

    /* map the shared memory */
    ptr = (struct start_times*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, FD, 0);

    pid_t pid;
    pid = fork();

    if (pid < 0) //fork failure
    {
        printf("ERROR!\n");
    }
    else if (pid == 0) //child process
    {
        gettimeofday(&current, NULL);
        ptr->seconds = current.tv_sec;
        ptr->microseconds = current.tv_usec;
        execvp(argv[1], &argv[1]);
    }
    else // for parent process
    {
        wait(NULL);
        gettimeofday(&current, NULL);

        elapsed_time = (current.tv_sec - ptr->seconds) + (current.tv_usec - ptr->microseconds)/1000000;
        printf("Elapsed time: %lf\n", elapsed_time);
    }
    shm_unlink(name);

    return 0;
}