#include <iostream> 
#include <time.h>
#include <limits.h>
#include <pthread.h>
#include <cstdlib>
#include <stdio.h> 
  
#define THREADS_NUMBER 4
#define INTERVAL 48000
using namespace std; 

long long *circle_points;
long long *square_points;

typedef struct {
    int tid;
} thread_data;

static long long MAX_NUMBER = 99990000.0;

void* calculate_pi(void* arg) { 
    long long interval, i; 
    long double rand_x, rand_y, origin_distance;
    thread_data *data= (thread_data*)arg;
    int tId = data->tid;

    unsigned int seed;
    seed = time(NULL);

    for (i = 0; i < MAX_NUMBER / THREADS_NUMBER; i++) { 
        int random_value_X = rand_r(&seed);
        int random_value_Y = rand_r(&seed);
        // printf("Random value X: %d Y: %d\n", random_value_X, random_value_Y);

        rand_x = double(random_value_X % (INTERVAL + 1)) / INTERVAL; 
        rand_y = double(random_value_Y % (INTERVAL + 1)) / INTERVAL; 
  
        // if (i < 30)
        //     printf("tId %d - X: %Lf Y: %Lf\n", tId, rand_x, rand_y);

        origin_distance = rand_x * rand_x + rand_y * rand_y; 
  
        if (origin_distance <= 1) {
            circle_points[tId]++; 
        }
  
        square_points[tId]++; 
    } 

    return NULL;
} 
  
int main() { 
    time_t start_t, end_t;
    double diff_t;
    pthread_t threads[THREADS_NUMBER]; 

    circle_points = new long long[THREADS_NUMBER];
    square_points = new long long[THREADS_NUMBER];

    thread_data data[THREADS_NUMBER];
    for (int i = 0; i < THREADS_NUMBER; i++) 
        data[i].tid = i;

    printf("Starting timer...\n");
    time(&start_t);  

    for (int i = 0; i < THREADS_NUMBER; i++) 
        pthread_create(&threads[i], NULL, calculate_pi, (void *)&data[i]); 
    
    for (int i = 0; i < THREADS_NUMBER; i++) 
        pthread_join(threads[i], NULL); 
  
    long double total_circle_points = 0; 
    for (int i = 0; i < THREADS_NUMBER; i++) 
        total_circle_points += circle_points[i]; 

    long double total_square_points = 0; 
    for (int i = 0; i < THREADS_NUMBER; i++) 
        total_square_points += square_points[i];
    
    long double pi = (long double) (4.0 * total_circle_points) / total_square_points;
  
    time(&end_t);
    diff_t = difftime(end_t, start_t);

    printf("Execution time = %f\n", diff_t);
    cout << "\nFinal Estimation of Pi = " << pi << "\n"; 

    // free memory
    delete circle_points;
    delete square_points;
     
    return 0; 
} 