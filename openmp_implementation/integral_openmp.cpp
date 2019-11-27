#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 6
#define NUM_REPS 200000000

unsigned int count;
long double total, inBox;
int x_min, x_max, y_min, y_max;

//The function that the integral should be calculated for
long double f (long double x){
  return exp(2 * sin(x) * sin(x));
}

//fcuntion that calculates the integral
long double integral (long double (*f)(long double), long double xmin, long double xmax, long double ymin, long double ymax){
  omp_set_num_threads( NUM_THREADS );
  inBox = 0;
  #pragma omp parallel private(count) shared(inBox) 
  {    //00000000
      #pragma omp for schedule(static)
      for (count=0; count < NUM_REPS; count++){
        long double u1 = (long double)rand()/(long double)RAND_MAX;
        long double u2 = (long double)rand()/(long double)RAND_MAX;

        long double xcoord = ((xmax - xmin)*u1) + xmin;
        long double ycoord = ((ymax - ymin)*u2) + ymin;
        long double val = f(xcoord);

        //std::cout << val << "    " << ycoord << "\n";
        if (val > ycoord) {
          inBox++;
        }
      }
  }

  total = (long double)NUM_REPS;
  long double density = inBox/total;
  return (xmax - xmin) * (ymax - ymin) * density;
}


int main(){
  std::cout<< "RESULT: " <<std::endl;
  long double result;
  x_min = -2;
  x_max = 2;
  y_min = 0;
  y_max = 4;
  clock_t t = clock(); 
  result = integral(f,-2,2,0,4);
  t = clock() - t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
  std::cout << result << std::endl;
  std::cout << "time taken: " << time_taken << std::endl;
  return 0;
}

