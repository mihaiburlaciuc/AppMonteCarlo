
#include <bits/stdc++.h> 
  
#define INTERVAL 1000
#include <limits.h> 
using namespace std; 

double calculate_pi() {
    unsigned long long  i; 
    double  rand_x, rand_y, origin_dist, pi; 
    unsigned long long circle_points = 0, square_points = 0; 

    srand(time(NULL)); 
        for (i = 0; i < UINT_MAX; i++) {  
            rand_x = double(rand() % (INTERVAL + 1)) / INTERVAL; 
            rand_y = double(rand() % (INTERVAL + 1)) / INTERVAL; 
      
            origin_dist = rand_x * rand_x + rand_y * rand_y; 
      
            if (origin_dist <= 1) 
                circle_points++; 
      
          	 square_points++; 
      
            pi = double(4 * circle_points) / square_points; 
        } 
  return pi;
  
}
  
int main() 
{   
    double pi;
    
    pi = calculate_pi();
    cout << "Final Estimation of Pi = " << pi << endl;  
    return 0; 
} 
