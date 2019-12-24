#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#define NUM_REPS 2000000000

int count;
double total = 0, inBox = 0;
int partial_inBoxes[10000];

// user defined function below
double f (double x){
  return exp(2 * sin(x) * sin(x));
}
//

//function to calculate a definite integral given bounds of integration (xmin/max) & bounds of function (ymin/ymax)
void integral (double (*f)(double), double xmin, double xmax, double ymin, double ymax){
  unsigned seed;
  #pragma omp parallel private(seed)
  {
    seed = time(NULL);
    int local_inBox = 0;
    #pragma omp for
    for (count=0; count < NUM_REPS; count++) {
      double u1 = (double)rand_r(&seed)/(double)RAND_MAX;
      double u2 = (double)rand_r(&seed)/(double)RAND_MAX;

      double xcoord = ((xmax - xmin)*u1) + xmin;
      double ycoord = ((ymax - ymin)*u2) + ymin;
      double val = f(xcoord);

      total++;

      if (val > ycoord) {
        local_inBox++;
      }
    }
    int tid = omp_get_thread_num();
    partial_inBoxes[tid] = local_inBox;
  }
  inBox = 0;
  //adun inBox-urile
  for(int i =0 ; i < omp_get_max_threads(); ++i)
    inBox += partial_inBoxes[i];
  double density = inBox/(double)NUM_REPS;
  double res =(xmax - xmin)*(ymax - ymin)*density;
  printf("%lf\n",res);
}


int main() {
printf("RESULT:");
integral(f,-2,2,0,4);
}
