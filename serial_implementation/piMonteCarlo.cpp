#include <iostream> 
#include <time.h>
#include <limits.h>
  
#define INTERVAL 48000 
using namespace std; 
  
int main() 
{ 
    long long interval, i; 
    long double rand_x, rand_y, origin_distance, pi; 
    long long circle_points = 0, square_points = 0; 

    srand(time(NULL)); 

    for (i = 0; i < UINT_MAX; i++) { 
        rand_x = double(rand() % (INTERVAL + 1)) / INTERVAL; 
        rand_y = double(rand() % (INTERVAL + 1)) / INTERVAL; 
  
        origin_distance = rand_x * rand_x + rand_y * rand_y; 
  
        if (origin_distance <= 1) {
            circle_points++; 
        }
  
        square_points++; 
  
        pi = double(4 * circle_points) / square_points; 
    } 
  
    cout << "\nFinal Estimation of Pi = " << pi; 
  
    return 0; 
} 