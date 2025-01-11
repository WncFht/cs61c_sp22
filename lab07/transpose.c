#include "transpose.h"

/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int *dst, int *src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}

/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
// void transpose_blocking(int n, int blocksize, int *dst, int *src) {
//     // 外层两个循环遍历块
//     for (int i = 0; i < n; i += blocksize) {
//         for (int j = 0; j < n; j += blocksize) {
//             // 内层两个循环处理当前块内的元素
//             for (int ii = i; ii < i + blocksize && ii < n; ii++) {
//                 for (int jj = j; jj < j + blocksize && jj < n; jj++) {
//                     dst[jj + ii * n] = src[ii + jj * n];
//                 }
//             }
//         }
//     }
// }
// 这个没有处理尾部的情况

void transpose_blocking(int n, int blocksize, int *dst, int *src) {
    // YOUR CODE HERE
    for (int bx = 0; bx + blocksize <= n; bx += blocksize) {
        for (int by = 0; by + blocksize <= n; by += blocksize) {
            for (int x = 0; x < blocksize; x ++) {
                for (int y = 0; y < blocksize; y ++) {
                    dst[by + y + (bx + x) * n] = src[bx + x + (by + y) * n];
                }
            }
        }
    }
    if (n % blocksize == 0) return;
    int ex = (n / blocksize) * blocksize;
    int ey = ex;
    for (int x = ex; x < n; x ++) {
        for (int y = 0; y < ey; y ++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
    for (int x = 0; x < ex; x ++) {
        for (int y = ey; y < n; y ++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
    for (int x = ex; x < n; x ++) {
        for (int y = ey; y < n; y ++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}
