#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

extern void compute_acceleration_asm(float *input_matrix, int *output_array, int Y);
struct timeval start_time, end_time;

void start_timer() {
    gettimeofday(&start_time, NULL);
}

double stop_timer() {
    gettimeofday(&end_time, NULL);
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    if (microseconds < 0) {
        seconds--;
        microseconds += 1000000;
    }
    return (double)seconds * 1000.0 + (double)microseconds / 1000.0;
}

int compute_acceleration_c(float Vi, float Vf, float T) {
    const float CONV_FACTOR = 1000.0f / 3600.0f;
    float delta_v_kmh = Vf - Vi;
    float delta_v_ms = delta_v_kmh * CONV_FACTOR;
    float acceleration = delta_v_ms / T;
    return (int)roundf(acceleration);
}
void generate_random_input(float *matrix, int Y) {
    srand(time(NULL));
    for (int i = 0; i < Y; i++) {
        matrix[i * 3 + 0] = (float)rand() / (float)RAND_MAX * 150.0f;
        matrix[i * 3 + 1] = matrix[i * 3 + 0] + (float)rand() / (float)RAND_MAX * (300.0f - matrix[i * 3 + 0]);
        matrix[i * 3 + 2] = 1.0f + (float)rand() / (float)RAND_MAX * 29.0f;
    }
}

int main() {
    int Y_sizes[] = {10, 100, 1000, 10000};
    int num_sizes = sizeof(Y_sizes) / sizeof(Y_sizes[0]);
    const int NUM_RUNS = 30;

    printf("Ethan Dela Cruz, Marc Dumaran\n");
    printf("=================================================================\n");

    int Y_sample = 3;
    float sample_input[] = {
        0.0f, 62.5f, 10.1f,
        60.0f, 122.3f, 5.5f,
        30.0f, 160.7f, 7.8f
    };
    int sample_output[3];

    compute_acceleration_asm(sample_input, sample_output, Y_sample);
    printf("\n1. Sample Input and Output\n");
    printf("-------------------------------------------------\n");
    printf("Input Vi, Vf, T \t| Acceleration m/s^2\n"); 
    printf("-------------------------------------------------\n");
    
    for (int i = 0; i < Y_sample; i++) {
        printf("%.1f, %.1f, %.1f\t| %d\n",
            sample_input[i * 3 + 0],
            sample_input[i * 3 + 1],
            sample_input[i * 3 + 2],
            sample_output[i]
        );
    }
    printf("-------------------------------------------------\n");
    printf("\n2. Performance Timing Avg of %d runs\n", NUM_RUNS);
    printf("-------------------------------------------------\n");
    printf("Size (Y)\tAvg Time (ms)\n");
    printf("-------------------------------------------------\n");

    for (int j = 0; j < num_sizes; j++) {
        int Y = Y_sizes[j];
        float *input_matrix = (float *)malloc(Y * 3 * sizeof(float));
        int *output_array = (int *)malloc(Y * sizeof(int));

        if (input_matrix == NULL || output_array == NULL) {
            perror("Memory allocation failed");
            if(input_matrix) free(input_matrix);
            if(output_array) free(output_array);
            return 1;
        }

        generate_random_input(input_matrix, Y);

        double total_time_ms = 0.0;

        for (int k = 0; k < NUM_RUNS; k++) {
            start_timer();
            compute_acceleration_asm(input_matrix, output_array, Y);
            total_time_ms += stop_timer();
        }

        double average_time_ms = total_time_ms / NUM_RUNS;
        printf("%d\t\t%.4f\n", Y, average_time_ms);

        free(input_matrix);
        free(output_array);
    }
    printf("-------------------------------------------------\n");

    return 0;
}
