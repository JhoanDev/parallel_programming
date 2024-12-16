#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_speedup(double sequential_time, double parallel_time);
double calculate_efficiency(double speedup, int processors);
double calculate_mean(double values[], int size);
double calculate_median(double values[], int size);
double calculate_min(double values[], int size);
void sort_values(double values[], int size);

int main()
{
    int option;
    double sequential_time, parallel_time, speedup, efficiency;
    int processors;
    double values[5];

    do
    {
        printf("\nCalculator Menu:\n");
        printf("1. Calculate Speedup\n");
        printf("2. Calculate Efficiency\n");
        printf("3. Calculate Mean, Median, and Min of 5 values\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        system("clear");

        switch (option)
        {
        case 1:
            printf("Enter sequential execution time: ");
            scanf("%lf", &sequential_time);
            printf("Enter parallel execution time: ");
            scanf("%lf", &parallel_time);
            speedup = calculate_speedup(sequential_time, parallel_time);
            printf("Speedup: %.6lf\n", speedup);
            break;

        case 2:
            printf("Enter speedup: ");
            scanf("%lf", &speedup);
            printf("Enter number of processors: ");
            scanf("%d", &processors);
            efficiency = calculate_efficiency(speedup, processors);
            printf("Efficiency: %.6lf\n", efficiency);
            break;

        case 3:
            printf("Enter 5 values: ");
            for (int i = 0; i < 5; i++)
            {
                scanf("%lf", &values[i]);
            }
            double mean = calculate_mean(values, 5);
            double median = calculate_median(values, 5);
            double min = calculate_min(values, 5);  // Calculando o mínimo
            printf("Mean: %.6lf\n", mean);
            printf("Median: %.6lf\n", median);
            printf("Minimum: %.6lf\n", min);  // Exibindo o mínimo
            break;

        case 4:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (option != 4);

    return 0;
}

double calculate_speedup(double sequential_time, double parallel_time)
{
    if (parallel_time <= 0)
    {
        printf("Error: Parallel time must be greater than 0.\n");
        exit(1);
    }
    return sequential_time / parallel_time;
}

double calculate_efficiency(double speedup, int processors)
{
    if (processors <= 0)
    {
        printf("Error: Number of processors must be greater than 0.\n");
        exit(1);
    }
    return speedup / processors;
}

double calculate_mean(double values[], int size)
{
    double sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum += values[i];
    }
    return sum / size;
}

double calculate_median(double values[], int size)
{
    sort_values(values, size);
    if (size % 2 == 0)
    {
        return (values[size / 2 - 1] + values[size / 2]) / 2.0;
    }
    else
    {
        return values[size / 2];
    }
}

double calculate_min(double values[], int size)
{
    double min = values[0];
    for (int i = 1; i < size; i++)
    {
        if (values[i] < min)
        {
            min = values[i];
        }
    }
    return min;
}

int cmp(const void *a, const void *b)
{
    double diff = *(double *)a - *(double *)b;
    if (diff > 0)
        return 1;
    else if (diff < 0)
        return -1;
    else
        return 0;
}

void sort_values(double values[], int size)
{
    qsort(values, size, sizeof(double), cmp);
}
