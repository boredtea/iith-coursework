#include <stdio.h>
#include <math.h>

//structure to store a point
struct Coordinates
{
    int x;
    int y;
};

//function to take input
void input(struct Coordinates *point, int n)
{
    printf("\n");
    //accepting serial number
    printf("Enter enter the coordinates of the point %d: ", n + 1);
    scanf("%d %d", &point->x, &point->y);  
}

//function to calculate factorial of a number
//used to calculate the combinations of two numbers
long long int factorial(int x)
{
    long long int factorial = 1;

    for(int i = 2; i <= x; i++)
        factorial = i * factorial;

    return factorial;
}

//function to compute combinations
long long int combinations(int N)
{
    long long int combination;

    combination = factorial(N) / (factorial(2) * factorial(N - 2));
    
    return combination;
}

//function which calculates distance between two points
//also displays and returns distance between two points
double distance(struct Coordinates *point1, struct Coordinates *point2, int p1, int p2)
{
    double distance;
    double inside = pow((point1->x - point2->x), 2) + pow((point1->y - point2->y), 2);
    distance = sqrt(inside);

    printf("\nDistance between (%d, %d): %lf\n", p1, p2, distance);

    return distance;
}
 

int main(int argc, char const *argv[])
{
    int N; //stores the number of points

    printf("\nEnter the number of points in your set: ");
    scanf("%d", &N);

    struct Coordinates points[N]; //creating structure array to store N points

    //taking input of point co-ordinates
    for(int i = 0; i < N; i++)
    {
        input(&points[i], i);
    }

    int pairs = combinations(N); //stores the number of all the pairs of points that can be formed

    double dis[pairs]; //stores the distance between every pair of points
    double dist; //used to store the distance between the current pair of points
    
    //store information pertaining to the distance between two points
    double max = 0;
    int max1, max2;

    int count = 0; //used to traverse along the dis array

    //loop to calculate distance between every two pairs of points
    for(int i = 0; i < N; i++)
    {
        for(int j = i + 1; j < N; j++)
        {
            dist = distance(&points[i], &points[j], i+1, j+1);
            dis[count++] = dist;

            //finding and storing the highest distance (and the corresponding coordinates)
            //encountered so far
            if(dist > max)
            {
                max = dist;
                max1 = i + 1;
                max2 = j + 1;
            }
        }
    }

    //displaying points responsible for the maximum distance
    printf("\nPoints corresponding to the maximum of distances: (%d, %d)\n\n", max1, max2);

    return 0;
}
