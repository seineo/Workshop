/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * trans_32 - Use local variables(stored in registers) to reduce misses.
 *    Along the diagonal(4 blocks), 8 + 8 + 7 = 23 misses. In other blocks,
 *    each has 8 + 8 = 16 misses. In total, 4*23 + 12*16 = 284 misses.
 */
char trans_32_desc[] = "32X32 transpose";
void trans_32(int M, int N, int A[N][M], int B[M][N]) {
    int i_c, j_c, k;
    int b_size = 8;
    //control loops
    for(i_c = 0;i_c < N;i_c += b_size) {
        for(j_c = 0;j_c < M;j_c += b_size) {
            //copy inside block
            for(k = i_c;k < i_c + b_size;++k) {
                int a0 = A[k][j_c], a1 = A[k][j_c + 1], a2 = A[k][j_c + 2];
                int a3 = A[k][j_c + 3], a4 = A[k][j_c + 4], a5 = A[k][j_c + 5];
                int a6 = A[k][j_c + 6], a7 = A[k][j_c + 7];
                B[j_c][k] = a0;
                B[j_c + 1][k] = a1;
                B[j_c + 2][k] = a2;
                B[j_c + 3][k] = a3;
                B[j_c + 4][k] = a4;
                B[j_c + 5][k] = a5;
                B[j_c + 6][k] = a6;
                B[j_c + 7][k] = a7;
            }
        }
    }
}

/*
 * trans_64 - Too hard for me.
 *          Reference: https://www.jianshu.com/p/e68dd8305e9c
 */
char trans_64_desc[] = "64x64 transpose";
void trans_64(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, k, tmp;
    int b_size = 8;
    int a0, a1, a2, a3, a4, a5, a6, a7;
    for (i = 0; i < N; i += b_size) {
        for (j = 0; j < M; j += b_size) {
            for (k = 0; k < b_size / 2; k++) {
                // A top left
                a0 = A[k + i][j];
                a1 = A[k + i][j + 1];
                a2 = A[k + i][j + 2];
                a3 = A[k + i][j + 3];

                // copy
                // A top right
                a4 = A[k + i][j + 4];
                a5 = A[k + i][j + 5];
                a6 = A[k + i][j + 6];
                a7 = A[k + i][j + 7];

                // B top left
                B[j][k + i] = a0;
                B[j + 1][k + i] = a1;
                B[j + 2][k + i] = a2;
                B[j + 3][k + i] = a3;

                // copy
                // B top right
                B[j + 0][k + 4 + i] = a4;
                B[j + 1][k + 4 + i] = a5;
                B[j + 2][k + 4 + i] = a6;
                B[j + 3][k + 4 + i] = a7;
            }
            for (k = 0; k < b_size / 2; k++) {
                // step 1 2
                a0 = A[i + 4][j + k], a4 = A[i + 4][j + k + 4];
                a1 = A[i + 5][j + k], a5 = A[i + 5][j + k + 4];
                a2 = A[i + 6][j + k], a6 = A[i + 6][j + k + 4];
                a3 = A[i + 7][j + k], a7 = A[i + 7][j + k + 4];
                // step 3
                tmp = B[j + k][i + 4], B[j + k][i + 4] = a0, a0 = tmp;
                tmp = B[j + k][i + 5], B[j + k][i + 5] = a1, a1 = tmp;
                tmp = B[j + k][i + 6], B[j + k][i + 6] = a2, a2 = tmp;
                tmp = B[j + k][i + 7], B[j + k][i + 7] = a3, a3 = tmp;
                // step 4
                B[j + k + 4][i + 0] = a0, B[j + k + 4][i + 4 + 0] = a4;
                B[j + k + 4][i + 1] = a1, B[j + k + 4][i + 4 + 1] = a5;
                B[j + k + 4][i + 2] = a2, B[j + k + 4][i + 4 + 2] = a6;
                B[j + k + 4][i + 3] = a3, B[j + k + 4][i + 4 + 3] = a7;
            }
        }
    }
}

int min(int a, int b) {
    return a < b ? a : b;
}

/*
 * trans_61 - Enumerate block size and find the minimum size is 23 
 */
char trans_61_desc[] = "61X67 transpose";
void trans_61(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, s, k;
    int a0, a1, a2, a3, a4, a5, a6, a7;
    for (i = 0; i < N; i += 8) {
    for (j = 0; j < M; j += 23) {
        if (i + 8 <= N && j + 23 <= M) {
            for (s = j; s < j + 23; s++) {
                a0 = A[i][s];
                a1 = A[i + 1][s];
                a2 = A[i + 2][s];
                a3 = A[i + 3][s];
                a4 = A[i + 4][s];
                a5 = A[i + 5][s];
                a6 = A[i + 6][s];
                a7 = A[i + 7][s];
                B[s][i + 0] = a0;
                B[s][i + 1] = a1;
                B[s][i + 2] = a2;
                B[s][i + 3] = a3;
                B[s][i + 4] = a4;
                B[s][i + 5] = a5;
                B[s][i + 6] = a6;
                B[s][i + 7] = a7;
            }
        } else {
            for (k = i; k < min(i + 8, N); k++) {
                for (s = j; s < min(j + 23, M); s++) {
                    B[s][k] = A[k][s];
                }
            }
        }
    }
}

}

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if(M == 32) {
        trans_32(M, N, A, B);
    }
    else if(M == 64) {
        trans_64(M, N, A, B);
    }
    else {
        trans_61(M, N, A ,B);
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans_64, trans_64_desc);
    registerTransFunction(trans_61, trans_61_desc);
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

