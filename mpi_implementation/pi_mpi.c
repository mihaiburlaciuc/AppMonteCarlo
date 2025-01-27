#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define INTERVAL 2000000000

static long long MAX_NUMBER = 2000000000;

int main(int argc, char* argv[]) { 
	int pid, np, 
    n_elements_recieved;

    long long square_points = 0;

	MPI_Status status;
    srand(time(NULL));

	// Creation of parallel processes
	MPI_Init(&argc, &argv);

	// find out process ID,
	// and how many processes were started
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

    long long elements_per_proc = MAX_NUMBER / np;

	// master process 
	if (pid == 0) { 
		struct timeval  start, stop;
  		gettimeofday(&start, NULL);
		
		int i; 
        long long circle_points = 0;
        // Run its own work
        long double rand_x, rand_y, origin_distance;

        for (i = 0; i < elements_per_proc; i++) {
            rand_x = (long double)(rand() % (INTERVAL + 1)) / INTERVAL;
            rand_y = (long double)(rand() % (INTERVAL + 1)) / INTERVAL;

            origin_distance = rand_x * rand_x + rand_y * rand_y;

            if (origin_distance <= 1) {
                circle_points++;
            }
        }

        long double total_circle_points = circle_points;
        //printf("Pid %d Sending circle points %lld\n", pid, circle_points);
        // total_square_points is equal with the max number
        long double total_square_points = MAX_NUMBER;

		// collects partial sums from other processes
		long long received_circle_points;
		for (i = 1; i < np; i++) {
			MPI_Recv(&received_circle_points, 1, MPI_LONG_LONG,
					MPI_ANY_SOURCE, 0,
					MPI_COMM_WORLD,
					&status);
            //printf("Received from %d #circlePoints %lld\n", i, received_circle_points);

			total_circle_points += received_circle_points;
		}

		long double pi = (long double) (4.0 * total_circle_points) / total_square_points;
        printf("Final execution of PI is %Lf\n", pi);

        gettimeofday(&stop, NULL);
  		printf ("Pi MPI with %d threads has a duration of %lf seconds\n",
          np,
          (double) (start.tv_usec - stop.tv_usec) / 1000000 +
          (double) (stop.tv_sec - start.tv_sec));
	} else {
        int i;
		long double rand_x, rand_y, origin_distance;

        long long circle_points = 0;

        for (i = 0; i < elements_per_proc; i++) {
            rand_x = (long double) (rand() % (INTERVAL + 1)) / INTERVAL;
            rand_y = (long double) (rand() % (INTERVAL + 1)) / INTERVAL;

            // printf ("X: %Lf Y: %Lf\n", rand_x, rand_y);

            origin_distance = rand_x * rand_x + rand_y * rand_y;

            if (origin_distance <= 1) {

                circle_points++;

                // printf ("Pid %d Circle Points %lld \n", pid, circle_points);
            }
        }

        //printf("Pid %d Sending circle points %lld\n", pid, circle_points);
		// Send the circle points
		MPI_Send(&circle_points, 1, MPI_LONG_LONG,
				0, 0, MPI_COMM_WORLD);
	}

	// cleans up all MPI state before exit of process
	MPI_Finalize();

	return 0;
}
