#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

unsigned int count;
float total, inBox;
int x_min, x_max, y_min, y_max;

//The function that the integral should be calculated for
float f (float x){
  return exp(2 * sin(x) * sin(x));
}

//fcuntion that calculates the integral
float integral (float (*f)(float), float xmin, float xmax, float ymin, float ymax){
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

  return (xmax - xmin) * (ymax - ymin) * density;
}


int main(){
  std::cout<< "RESULT: " <<std::endl;
  float result;
  x_min = -1000;
  x_max = 1000;
  y_min = 0;
  y_max = 40000;
  result = integral(f,-1000,1000,0,400000);
  std::cout << result << std::endl;
  return 0;
}

