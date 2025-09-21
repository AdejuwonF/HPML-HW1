#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <mkl_cblas.h>

float bdp(long N, float *pA, float *pB) {
  float R = cblas_sdot(N, pA, 1, pB, 1);
  return R; 
}

int main(int argc, char * argv[]){
    if (argc < 3) {
        printf("Insufficient arguments.  Please provide input for vector size and number of measurements\n");
        return 0;
    }
    int n, num_measurements;
    num_measurements = atoi(argv[2]);
    n = atoi(argv[1]);
    printf("Vector Size: %d, Number of Measurements: %d\n", n, num_measurements);

    float* pA = malloc(sizeof(float) * n);
    float* pB = malloc(sizeof(float) * n);
    for (int i = 0; i < n; i++){
        pA[i] = 1.0;
        pB[i] = 1.0;
    }

    double total_time_spent = 0.0;
    double time_spent = 0.0;
    struct timespec start, end;
    for (int i = 0; i < num_measurements; i++){
        clock_gettime(CLOCK_REALTIME, &start);
        volatile float product = bdp(n, pA, pB);
        clock_gettime(CLOCK_REALTIME, &end);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("Time Spent on iteration %d: %f\n", i, time_spent);
        if (i >= num_measurements / 2){
          total_time_spent += time_spent;
        }
    }
    double average_time_spent = total_time_spent / (num_measurements / 2);
    printf("Time Spent on 2nd half of experiments.  Total: %f, Average: %f\n", total_time_spent, average_time_spent);
    // One multiplication and addition per element in array.
    printf("FLOP(s): %f\n", 2*n / average_time_spent);
    // Two floats processed per element.
    printf("GB(s): %f\n", (2*sizeof(float)*n / average_time_spent) / 1000000000.0);
    

}