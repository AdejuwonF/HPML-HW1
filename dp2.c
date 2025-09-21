#include <time.h>
#include <stdio.h>
#include <stdlib.h>

float dpunroll(long N, float *pA, float *pB) {
  float R = 0.0;
  int j;
  for (j=0;j<N;j+=4)
    R += pA[j]*pB[j] + pA[j+1]*pB[j+1] \
           + pA[j+2]*pB[j+2] + pA[j+3] * pB[j+3];
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
        volatile float result = dpunroll(n, pA, pB);
        clock_gettime(CLOCK_REALTIME, &end);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("Time Spent on iteration %d: %f\n", i, time_spent);
        if (i >= num_measurements / 2){
          total_time_spent += time_spent;
        }
    }
    double average_time_spent = total_time_spent / (num_measurements / 2);
    printf("Time Spent on 2nd half of experiments.  Total: %f, Average: %f\n", total_time_spent, average_time_spent);
    // 9 ops per iteration.  n/4 iterations
    printf("FLOP(s): %f\n", 9*(n/4.0) / average_time_spent);
    // 8 floats processed per iteration.  n/4 iterations
    printf("GB(s): %f\n", (8*sizeof(float)*(n/4.0) / average_time_spent) / 1000000000.0);
    

}