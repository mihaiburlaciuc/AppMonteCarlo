#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <sys/time.h>

unsigned long long count;
double total, inBox;
int x_min, x_max, y_min, y_max;

//The function that the integral should be calculated for
float f (float x){
  return exp(2 * sin(x) * sin(x));
}

//fcuntion that calculates the integral
void integral (float (*f)(float), float xmin, float xmax, float ymin, float ymax){
  for (count=0; count < 2000000000; count++){
    float u1 = (float)rand()/(float)RAND_MAX;
    float u2 = (float)rand()/(float)RAND_MAX;

    float xcoord = ((xmax - xmin)*u1) + xmin;
    float ycoord = ((ymax - ymin)*u2) + ymin;
    float val = f(xcoord);

    total++;

    if (val > ycoord){
      inBox++;
    }
  }

  float density = inBox/total;

  double res =(xmax - xmin)*(ymax - ymin)*density;
  printf("%lf\n",res);
}


int main(int argc, char *argv[]) {
  std::cout<< "RESULT: " <<std::endl;
  x_min = -1000;
  x_max = 1000;
  y_min = 0;
  y_max = 40000;
  struct timeval  start, stop;
  gettimeofday(&start, NULL);
  integral(f,-2,2,0,4);
  gettimeofday(&stop, NULL);
  printf ("Integral serial version has a duration of %lf seconds\n",
          (double) (start.tv_usec - stop.tv_usec) / 1000000 +
          (double) (stop.tv_sec - start.tv_sec));  
  return 0;
}

