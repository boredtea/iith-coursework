#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#define MAXSIZE 100000
#define MAX_THREADS 16
#define MAX_POINTS 6000

int n_threads;
int source_x, source_y;
int n_points;
int dest_x[MAX_POINTS];
int dest_y[MAX_POINTS];
int count_per_thread;

// global variables required for the function
double distances[MAX_POINTS]; // stores distances from source to all coordinates
double min_distances[MAX_THREADS]; // stores the min distance found by each thread
int min_coord_index[MAX_THREADS]; // stores the index of the min distance coordinate per thread
int idx = -1; // variable to keep track of starting index per thread in the overall arrays

// function to calculate the distance between two points
double euclidean_dist(int x1, int y1, int x2, int y2)
{
  double sum = pow(x1 - x2, 2) + pow(y1 - y2, 2);
  double dist = sqrt(sum);
  return dist;
}

// thread function to find the minimum distance within each thread
void* min_dist(void* args)
{
  idx++;
  int start_index = idx * count_per_thread;

  double dist;
  double min_d = 0;
  int min_coord = start_index;
  // loop to iterate through each point passed to a thread
  for(int i = start_index; i < start_index + count_per_thread; i++)
  {
    if (i >= n_points)
      break;
    
    dist = euclidean_dist(source_x, source_y, dest_x[i], dest_y[i]);
    distances[i] = dist;

    if (i == start_index)
      min_d = dist;
    
    if(dist < min_d)
    {
      min_d = dist;
      min_coord = i;
    }
  }
  min_distances[idx] = min_d;
  min_coord_index[idx] = min_coord;

  return NULL;
}

int main()
{
  struct timeval start, end;

  // reading input from the input file
  FILE *file_pointer;
  char line[MAXSIZE];
  int x;
  int line_number = 0;

  file_pointer = fopen("input.txt", "r");
  if (file_pointer == NULL) {
      fprintf(stderr, "%s\n", "Error reading from file");
      exit(EXIT_FAILURE);
  }

  // while loop to read entire file
  while (fgets(line, MAXSIZE, file_pointer) != NULL) {
    line_number++;

    // code to read each line
    char delim[] = "( , ) ";
    char *ptr = strtok(line, delim);

    switch (line_number)
    {
      // reading the number of threads
      case 1: n_threads = atoi(line);
              break;
      // reading the source coordinates        
      case 2: 
              for(int i = 1; i <= 2; i++)
              {
                if (i == 1)
                  source_x = atoi(ptr);
                else if(i == 2)
                  source_y = atoi(ptr);
                ptr = strtok(NULL, delim);
              }
              break;
      // reading the number of destination coordinates        
      case 3: n_points = atoi(line);
              break;
      // reading the destination coordinates       
      case 4: for(int i = 0; i < 2 * n_points; i++)
              {
                if (i % 2 == 0)
                  dest_x[i / 2] = atoi(ptr);
                else if(i % 2 == 1)
                  dest_y[i / 2] = atoi(ptr);
                ptr = strtok(NULL, delim);
              }
              break;
    }
    ptr = NULL;
  }
  fclose(file_pointer);
  count_per_thread = n_points/n_threads;


  // declaring required number of threads
  pthread_t threads[n_threads];

  // start of execution
  gettimeofday(&start, NULL);
  // creating the threads
  for(int i = 0; i < n_threads; i++)
  {
    pthread_create(&threads[i], NULL, min_dist, NULL);
  }

  // joining all the threads
  for (int i = 0; i < n_threads; i++)
    pthread_join(threads[i], NULL); 
  
  // find the overall min distance
  double overall_min = min_distances[0];
  int min_index = 0;
  for(int i = 1; i < n_threads; i++)
  {
    // printf("%d %lf %d\n", i, min_distances[i], min_coord_index[i]);
    if (min_distances[i] < overall_min)
    {
      overall_min = min_distances[i];
      min_index = min_coord_index[i];
    }
  }

  // end of execution
  gettimeofday(&end, NULL);
  // calculating the elapsed time
  long unsigned seconds = (end.tv_sec - start.tv_sec);
  long unsigned micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

  // print output
  printf("%ld microseconds\n(%d,%d)\n", micros, dest_x[min_index], dest_y[min_index]);

  return 0;
}

