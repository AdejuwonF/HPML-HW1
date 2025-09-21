import numpy as np
import sys
import time

# for a simple loop
def dp(A,B):
    R = np.dot(A, B);
    return R


def main():
    if len(sys.argv) < 3:
        print("Please provide both the vector size and number of measuerments as arguments")
        return
    n = int(sys.argv[1])
    num_measurements = int(sys.argv[2])
    print("Running experiment with vector size {0} for {1} measurements".format(n, num_measurements))

    A = np.ones(n,dtype=np.float32)
    B = np.ones(n,dtype=np.float32)
    time_elapsed = 0
    total_time_spent = 0
    for i in range(num_measurements):
        start_time = time.perf_counter()
        dp(A, B)
        end_time = time.perf_counter()
        time_elapsed = end_time - start_time
        print("Time spend on iteration {0}: {1}".format(i, time_elapsed))
        if (i >= num_measurements/2):
            total_time_spent += time_elapsed
    average_time_spent = total_time_spent / (num_measurements/2)
    print("Time Spent on 2nd half of experiments.  Total: {0}, Average: {1}".format(total_time_spent, average_time_spent));
    #  One multiplication and addition per element in array.
    print("FLOP(s): {0}".format(2*n / average_time_spent));
    #  Two floats processed per element.
    print("GB(s): {0}".format((2*4*n / average_time_spent) / 1000000000.0));
    
if __name__ == "__main__":
    main()
