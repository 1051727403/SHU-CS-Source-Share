#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main(int argc, char *argv[]) {
    int i, j, k;

    double *a, *b, *c;
    a = (double *) malloc(N * N * sizeof(double));
    b = (double *) malloc(N * N * sizeof(double));
    c = (double *) malloc(N * N * sizeof(double));

    double start, end;
    double cpu_time_used, serial_time_used, ratio;

    //初始化矩阵
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            *(a + i * N + j) = i + j;
            *(b + i * N + j) = i * j;
            *(c + i * N + j) = 0;
        }
    }

    // 串行
    start = omp_get_wtime();

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            *(c + i * N + j) = 0;

            for (k = 0; k < N; k++) {
                *(c + i * N + j) += *(a + i * N + k) * *(b + k * N + j);
            }
        }
    }

    end = omp_get_wtime();
    serial_time_used = end - start;

    printf("串行计算时间:%f\n", serial_time_used);

    // 1线程并行
    start = omp_get_wtime();

#pragma omp parallel num_threads(1)
    {
#pragma omp for private(i, j, k)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                *(c + i * N + j) = 0;

                for (k = 0; k < N; k++) {
                    *(c + i * N + j) += *(a + i * N + k) * *(b + k * N + j);
                }
            }
        }
    }

    end = omp_get_wtime();
    cpu_time_used = end - start;
    ratio = serial_time_used / cpu_time_used;

    printf("1线程并行计算时间:%f, 加速比:%f\n", cpu_time_used, ratio);

    // 2线程并行
    start = omp_get_wtime();

#pragma omp parallel num_threads(2)
    {
#pragma omp for private(i, j, k)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                *(c + i * N + j) = 0;

                for (k = 0; k < N; k++) {
                    *(c + i * N + j) += *(a + i * N + k) * *(b + k * N + j);
                }
            }
        }
    }

    end = omp_get_wtime();
    cpu_time_used = end - start;
    ratio = serial_time_used / cpu_time_used;

    printf("2线程并行计算时间:%f, 加速比:%f\n", cpu_time_used, ratio);

    // 4线程并行
    start = omp_get_wtime();

#pragma omp parallel num_threads(4)
    {
#pragma omp for private(i, j, k)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                *(c + i * N + j) = 0;

                for (k = 0; k < N; k++) {
                    *(c + i * N + j) += *(a + i * N + k) * *(b + k * N + j);
                }
            }
        }
    }

    end = omp_get_wtime();
    cpu_time_used = end - start;
    ratio = serial_time_used / cpu_time_used;

    printf("4线程并行计算时间:%f, 加速比:%f\n", cpu_time_used, ratio);

    // 8线程并行
    start = omp_get_wtime();

#pragma omp parallel num_threads(8)
    {
#pragma omp for private(i, j, k)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                *(c + i * N + j) = 0;

                for (k = 0; k < N; k++) {
                    *(c + i * N + j) += *(a + i * N + k) * *(b + k * N + j);
                }
            }
        }
    }

    end = omp_get_wtime();
    cpu_time_used = end - start;
    ratio = serial_time_used / cpu_time_used;

    printf("8线程并行计算时间:%f, 加速比:%f\n", cpu_time_used, ratio);

    // 16线程并行
    start = omp_get_wtime();

#pragma omp parallel num_threads(16)
    {
#pragma omp for private(i, j, k)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                *(c + i * N + j) = 0;

                for (k = 0; k < N; k++) {
                    *(c + i * N + j) += *(a + i * N + k) * *(b + k * N + j);
                }
            }
        }
    }

    end = omp_get_wtime();
    cpu_time_used = end - start;
    ratio = serial_time_used / cpu_time_used;

    printf("16线程并行计算时间:%f, 加速比:%f\n", cpu_time_used, ratio);

    // 32线程并行
    start = omp_get_wtime();

#pragma omp parallel num_threads(32)
    {
#pragma omp for private(i, j, k)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                *(c + i * N + j) = 0;

                for (k = 0; k < N; k++) {
                    *(c + i * N + j) += *(a + i * N + k) * *(b + k * N + j);
                }
            }
        }
    }

    end = omp_get_wtime();
    cpu_time_used = end - start;
    ratio = serial_time_used / cpu_time_used;

    printf("32线程并行计算时间:%f, 加速比:%f\n", cpu_time_used, ratio);


    free(a);
    free(b);
    free(c);

    return 0;
}
