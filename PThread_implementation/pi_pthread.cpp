#include <iostream> 
#include <time.h>
#include <limits.h>
#include <pthread.h>
#include <cstdlib>
#include <stdio.h> 
  
#define INTERVAL 2000000000
using namespace std; 

long long circle_points[500];
long long square_points[500];
int threads_number;

typedef struct {
    int tid;
} thread_data;

static long long MAX_NUMBER = 2000000000;

void* calculate_pi(void* arg) { 
    long long interval, i; 
    long double rand_x, rand_y, origin_distance;
    thread_data *data= (thread_data*)arg;
    int tId = data->tid;

    unsigned int seed;
    seed = time(NULL);

    int local_circle_points = 0;
    int local_total_points = 0;

    for (i = 0; i < MAX_NUMBER / threads_number; i++) { 
        int random_value_X = rand_r(&seed);
        int random_value_Y = rand_r(&seed);
        // printf("Random value X: %d Y: %d\n", random_value_X, random_value_Y);

        rand_x = double(random_value_X % (INTERVAL + 1)) / INTERVAL; 
        rand_y = double(random_value_Y % (INTERVAL + 1)) / INTERVAL; 
  
        // if (i < 30)
        //     printf("tId %d - X: %Lf Y: %Lf\n", tId, rand_x, rand_y);

        origin_distance = rand_x * rand_x + rand_y * rand_y; 
        

        if (origin_distance <= 1) {
            local_circle_points++; 
        }
  
        local_total_points++; 
    } 

    circle_points[tId] = local_circle_points;
    square_points[tId] = local_total_points;

    return NULL;
} 
  
int main(int argc, char *argv[]) {
    threads_number = atoi(argv[1]);
    time_t start_t, end_t;
    double diff_t;
    pthread_t threads[threads_number]; 

    // circle_points = new long long[threads_number];
    // square_points = new long long[threads_number];

    thread_data data[threads_number];
    for (int i = 0; i < threads_number; i++) 
        data[i].tid = i;

    printf("Starting timer...\n");
    time(&start_t);  

    for (int i = 0; i < threads_number; i++) 
        pthread_create(&threads[i], NULL, calculate_pi, (void *)&data[i]); 
    
    for (int i = 0; i < threads_number; i++) 
        pthread_join(threads[i], NULL); 
  
    long double total_circle_points = 0; 
    for (int i = 0; i < threads_number; i++) 
        total_circle_points += circle_points[i]; 

    long double total_square_points = 0; 
    for (int i = 0; i < threads_number; i++) 
        total_square_points += square_points[i];
    
    long double pi = (long double) (4.0 * total_circle_points) / total_square_points;
  
    time(&end_t);
    diff_t = difftime(end_t, start_t);

    printf("Execution time for pi_pthread with %d threads = %f\n", threads_number,diff_t);
    cout << "Final Estimation of Pi = " << pi << "\n\n"; 

    // free memory
    // delete circle_points;
    // delete square_points;
     
    return 0; 
} 