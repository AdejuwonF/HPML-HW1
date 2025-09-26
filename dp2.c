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

float arithmetic_mean(float* measurements, int num_measurements){
  float agg = 0.0;
  for (int i = 0; i < num_measurements; i++){
    agg += measurements[i];
  }
  return agg / num_measurements;
}

float harmonic_mean(float* measurements, int num_measurements){
  float agg = 0.0;
  for (int i = 0; i < num_measurements; i++){
    agg += (1 / measurements[i]);
  }
  return num_measurements / agg;
}

int main(int argc, char * argv[]){
    if (argc < 3) {
        printf("Insufficient arguments.  Please provide input for vector size and number of measurements\n");
        return 0;
    }
    int n, num_trials, num_measurements;
    num_trials = atoi(argv[2]);
    num_measurements = num_trials / 2;
    n = atoi(argv[1]);
    //printf("Vector Size: %d, Number of Trials: %d\n", n, num_trials);

    float* measuerments = malloc(sizeof(float) * (num_measurements));
    float* pA = malloc(sizeof(float) * n);
    float* pB = malloc(sizeof(float) * n);
    for (int i = 0; i < n; i++){
        pA[i] = 1.0;
        pB[i] = 1.0;
    }

    double total_time_spent = 0.0;
    double time_spent = 0.0;
    struct timespec start, end;
    volatile float product;
    for (int i = 0; i < num_trials; i++){
        clock_gettime(CLOCK_REALTIME, &start);
        product = dpunroll(n, pA, pB);
        clock_gettime(CLOCK_REALTIME, &end);
        time_spent = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        //printf("Time Spent on iteration %d: %f\n", i, time_spent);
        if (i >= num_measurements){
          measuerments[i - num_measurements] = time_spent;
          total_time_spent += time_spent;
        }
    }
    // printf("Time Spent on 2nd half of experiments.  Total: %f, Arithmetic Average: %f\n", total_time_spent, arithmetic_mean(measuerments, num_measurements));
    // // One multiplication and addition per element in array.
    // printf("FLOP(s) Harmonic Mean: %f \n",  8*(n/4.0)/harmonic_mean(measuerments, num_measurements));
    // // Two floats processed per element.
    // printf("GB(s) Harmonic Mean:%f\n",
    //      8*sizeof(float)*(n/4.0)/harmonic_mean(measuerments, num_measurements) / 1000000000.0);
    // printf("Result: %f\n", product);
    printf("N: %d <T>: %f sec  B: %f GB/sec   F: %f FLOP/sec\n", 
            n,
            arithmetic_mean(measuerments, num_measurements), 
            2*sizeof(float)*n/harmonic_mean(measuerments, num_measurements) / 1000000000.0,
            2*n/harmonic_mean(measuerments, num_measurements));
}