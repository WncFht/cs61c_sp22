#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "transpose.h"

double benchmark(int *A, int *B, int n, int blocksize,
    void (*transpose)(int, int, int*, int*), char *description) {

    int i, j;

    /* initialize A,B to random integers */
    srand(time(NULL));
    for(i = 0; i < n*n; i++) 
        A[i] = rand();
    for(i = 0; i < n*n; i++) B[i] = rand();

    /* measure performance */
    struct timeval start, end;

    gettimeofday( &start, NULL );
    transpose( n, blocksize, B, A );
    gettimeofday( &end, NULL );

    double seconds = (end.tv_sec - start.tv_sec) +
        1.0e-6 * (end.tv_usec - start.tv_usec);

    /* check correctness */
    for( i = 0; i < n; i++ ) {
        for( j = 0; j < n; j++ ) {
            if( B[j+i*n] != A[i+j*n] ) {
                printf("Error!!!! Transpose does not result in correct answer!!\n");
                exit( -1 );
            }
        }
    }
    
    return seconds*1e3;
}

int main(int argc, char **argv) {
    printf("=== 实验1：固定 blocksize=20，变化 n ===\n");
    int test_n[] = {100, 1000, 2000, 5000, 10000};
    int blocksize = 20;
    
    for(int i = 0; i < 5; i++) {
        int n = test_n[i];
        int *A = (int*)malloc(n*n*sizeof(int));
        int *B = (int*)malloc(n*n*sizeof(int));
        
        double time1 = benchmark(A, B, n, blocksize, transpose_naive, "naive transpose");
        double time2 = benchmark(A, B, n, blocksize, transpose_blocking, "transpose with blocking");
        
        printf("\nn=%d, blocksize=%d:\n", n, blocksize);
        printf("naive: %.3f ms\n", time1);
        printf("blocking: %.3f ms\n", time2);
        printf("speedup: %.2fx\n", time1/time2);
        
        free(A);
        free(B);
    }
    
    printf("\n=== 实验2：固定 n=10000，变化 blocksize ===\n");
    int n = 10000;
    int test_blocksize[] = {50, 100, 500, 1000, 5000};
    
    for(int i = 0; i < 5; i++) {
        blocksize = test_blocksize[i];
        int *A = (int*)malloc(n*n*sizeof(int));
        int *B = (int*)malloc(n*n*sizeof(int));
        
        double time1 = benchmark(A, B, n, blocksize, transpose_naive, "naive transpose");
        double time2 = benchmark(A, B, n, blocksize, transpose_blocking, "transpose with blocking");
        
        printf("\nn=%d, blocksize=%d:\n", n, blocksize);
        printf("naive: %.3f ms\n", time1);
        printf("blocking: %.3f ms\n", time2);
        printf("speedup: %.2fx\n", time1/time2);
        
        free(A);
        free(B);
    }
    
    return 0;
}
