#include <stdio.h>
#include <omp.h>
#include <time.h>

double calc_pi_serial(long long n) {
    double x, sum = 0.0;
    const double step = 1.0 / n;

    for (long long i = 0; i < n; i++) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1 + x * x);
    }

    return step * sum;
}

double calc_pi_parallel(long long n, long long num_threads) {
    double x, sum = 0.0;
    const double step = 1.0 / n;

#pragma omp parallel num_threads(num_threads)
    {
        long long tid = omp_get_thread_num();
        long long num_t = omp_get_num_threads();

        double partial_sum = 0.0;
        long long start = tid * n / num_t;
        long long end = (tid + 1) * n / num_t;

#pragma omp for schedule(static)
        for (long long i = start; i < end; i++) {
            x = (i + 0.5) * step;
            partial_sum += 4.0 / (1 + x * x);
        }

#pragma omp critical
        {
            sum += partial_sum;
        }
    }

    return step * sum;
}

int main() {
    long long n = 1000000000;
    double pi_seq, pi_par;
    long long num_threads = 8;

    printf("开始串行计算...\n");
    clock_t start = clock();
    pi_seq = calc_pi_serial(n);
    clock_t end = clock();
    printf("串行计算结果：%lf\n", pi_seq);
    printf("串行计算时间：%ld 毫秒\n\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    printf("开始并行计算...\n");
    start = clock();
    pi_par = calc_pi_parallel(n, num_threads);
    end = clock();
    printf("并行计算结果：%lf\n", pi_par);
    printf("并行计算时间：%ld 毫秒\n", (end - start) * 1000 / CLOCKS_PER_SEC);

    return 0;
}
