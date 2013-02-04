#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

#define M 90
#define N 80

int sum_array_3d_bad_locality(int a[M][N][N])
{
    int i, j, k, sum = 0;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            for (k = 0; k < M; k++)
                sum += a[k][i][j];

    return sum;
}

int sum_array_3d_good_locality(int a[M][N][N])
{
    int i, j, k, sum = 0;

    for (k = 0; k < M; k++)
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                sum += a[k][i][j];

    return sum;
}

struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

int main(int argc, char **argv)
{
    int arr[M][N][N], i = 0;
    int iterations = 100;
    struct timespec bad_locality_time_begin, bad_locality_time_end;
    struct timespec good_locality_time_begin, good_locality_time_end;
    struct timespec time_diff;
    double total_bad_locality = 0.0, total_good_locality = 0.0;
    char locality_time_str[100];

    if ( argc > 1 )
    {
        iterations = strtol(argv[1], NULL, 10);
        if (errno == EINVAL || errno == ERANGE ||
            argv[1][0] < '0' || argv[1][0] > '9')
        {
            fprintf(stderr, "Usage: %s [iterations]\n", argv[0]);
            return 1;
        }
    }

    printf("Running test with %d iterations.\n", iterations);
    printf("Test array is %d bytes in size.\n", M*N*N*sizeof(int));

    clock_gettime(CLOCK_MONOTONIC,&bad_locality_time_begin);
    do
    {
        memset((void *)&arr, 1, M*N*N*sizeof(int));
        sum_array_3d_bad_locality(arr);
    } while (++i < iterations);
    clock_gettime(CLOCK_MONOTONIC,&bad_locality_time_end);

    i = 0;
    clock_gettime(CLOCK_MONOTONIC,&good_locality_time_begin);
    do
    {
        memset((void *)&arr, 1, M*N*N*sizeof(int));
        sum_array_3d_good_locality(arr);
    } while(++i < iterations);
    clock_gettime(CLOCK_MONOTONIC,&good_locality_time_end);

    time_diff = diff(bad_locality_time_begin, bad_locality_time_end);
    sprintf(locality_time_str, "%u.%09u", time_diff.tv_sec, time_diff.tv_nsec);
    total_bad_locality = strtod(locality_time_str, NULL);
    printf("Time spent running bad locality: %.9f sec.\n", total_bad_locality);

    time_diff = diff(good_locality_time_begin, good_locality_time_end);
    sprintf(locality_time_str, "%u.%09u", time_diff.tv_sec, time_diff.tv_nsec);
    total_good_locality = strtod(locality_time_str, NULL);
    printf("Time spent running good locality: %u.%09u sec.\n", time_diff.tv_sec, time_diff.tv_nsec);

    printf("Difference between averages: %.9f sec.\n", total_bad_locality - total_good_locality);

    return 0;
}