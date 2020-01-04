#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <mpi.h>
#include <sys/time.h>
#define NUM_REPS 2000000000

unsigned int count;
//The function that the integral should be calculated for
float f (float x){
  return exp(2 * sin(x) * sin(x));
}

//fcuntion that calculates the integral
void integral (float (*f)(float), float xmin, float xmax, float ymin, float ymax) {
    int world_size;
    double inBox;
    MPI_Status status;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        inBox = 0;
        int chunk  = NUM_REPS / (world_size - 1);
        int dest = 1;
        for(int start = 0; start < world_size - 1; ++start) {
          int dim = chunk;
          if(start == 0) // primiului thread ii trimit mai mult (cu num_reps/chunk)
            dim += NUM_REPS % chunk;
          MPI_Send(&dim, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
          dest++;
        }
        for(int i = 1; i < world_size; ++i) {
          int partial_inBox;
          MPI_Recv(&partial_inBox, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
          inBox += (double)partial_inBox;
        }

        float density = (float)inBox/(float)NUM_REPS;
        float res = (xmax - xmin) * (ymax - ymin) * density;
        printf("%f\n",res);
    }
    else
    {
      int local_inBox = 0;
      int local_dim;
      MPI_Recv(&local_dim, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

      unsigned seed = time(NULL);

      for (int count = 0; count < local_dim; count++) {
        float u1 = (float)rand_r(&seed)/(float)RAND_MAX;
        float u2 = (float)rand_r(&seed)/(float)RAND_MAX;

        float xcoord = ((xmax - xmin)*u1) + xmin;
        float ycoord = ((ymax - ymin)*u2) + ymin;
        float val = f(xcoord);

        if (val > ycoord) {
           local_inBox++;
        }
      }
      MPI_Send(&local_inBox, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
   }
}


int main(){
  int world_size;
  MPI_Status status;
  int rank;
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  srand(time(NULL));
<<<<<<< HEAD
  struct timeval  start, stop;
  if(rank == 0) {
    printf("RESULT: ");
    gettimeofday(&start, NULL);
  }
=======
  if(rank == 0)
    printf("RESULT: ");
>>>>>>> c6d906fd7d318d66684c2228f1be0c8604411e44
  integral(f,-2,2,0,4);
  if(rank == 0) {
    gettimeofday(&stop, NULL);
    printf ("Integral MPI with %d threads has a duration of %lf seconds\n",
            world_size,
            (double) (start.tv_usec - stop.tv_usec) / 1000000 +
            (double) (stop.tv_sec - start.tv_sec));
  }
  MPI_Finalize();
  return 0;
}
