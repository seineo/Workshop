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
 * trans_32 - Use blocking and local variables(stored in registers) to 
 *    reduce misses. Along the diagonal(4 blocks), 8 + 8 + 7 = 23 misses.
 *    In other blocks, each has 8 + 8 = 16 misses. In total, 4*23 + 12*16
 *    = 284 misses.
 */
char trans_32_desc[] = "32X32 transpose";
void trans_32(int M, int N, int A[N][M], int B[M][N]) {
    int i, j_c, k;
    int b_size = 8;
    //control loops
    for(i = 0;i < N;i += b_size) {
        for(j_c = 0;j_c < M;j_c += b_size) {
            //copy inside block
            for(k = i;k < i + b_size;++k) {
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
 * trans_64 - Use blocking and complex copy.
 *          Reference: https://zhuanlan.zhihu.com/p/28585726
 */
char trans_64_desc[] = "64x64 transpose";
void trans_64(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, k, temp;
    int b_size = 8;
    int a0, a1, a2, a3, a4, a5, a6, a7;
    //control loop
    for(i = 0;i < N;i += b_size) {
        for(j = 0;j < M;j += b_size) {
            //copy inside block(complex)
            for(k = 0;k < b_size / 2;++k) {
                a0 = A[i + k][j];   a1 = A[i + k][j + 1];
                a2 = A[i + k][j + 2];   a3 = A[i + k][j + 3];
                a4 = A[i + k][j + 4];   a5 = A[i + k][j + 5];
                a6 = A[i + k][j + 6];   a7 = A[i + k][j + 7];
                B[j][i + k] = a0;   B[j + 1][i + k] = a1;
                B[j + 2][i + k] = a2;   B[j + 3][i + k] = a3;
                B[j][i + k + 4] = a4;   B[j + 1][i + k + 4] = a5;
                B[j + 2][i + k + 4] = a6;   B[j + 3][i + k + 4] = a7;
            }
            for(k = 0;k < b_size / 2;++k) {
                a0 = A[i + 4][j + k];   a1 = A[i + 5][j + k];
                a2 = A[i + 6][j + k];   a3 = A[i + 7][j + k];
                a4 = A[i + 4][j + k + 4];   a5 = A[i + 5][j + k + 4];
                a6 = A[i + 6][j + k + 4];   a7 = A[i + 7][j + k + 4];
                temp = B[j + k][i + 4]; B[j + k][i + 4] = a0;   a0 = temp;
                temp = B[j + k][i + 5]; B[j + k][i + 5] = a1;   a1 = temp;
                temp = B[j + k][i + 6]; B[j + k][i + 6] = a2;   a2 = temp;
                temp = B[j + k][i + 7]; B[j + k][i + 7] = a3;   a3 = temp;
                B[j + k + 4][i] = a0;   B[j + k + 4][i + 1] = a1;  
                B[j + k + 4][i + 2] = a2;   B[j + k + 4][i + 3] = a3;
                B[j + k + 4][i + 4] = a4;   B[j + k + 4][i + 5] = a5;
                B[j + k + 4][i + 6] = a6;   B[j + k + 4][i + 7] = a7;
            }
        }
    }
}


/*
 * trans_61 - Enumerate block size and find size 16 is ok.
 *            Then use blocking and block size is 16.
 */
char trans_61_desc[] = "61X67 transpose";
void trans_61(int M, int N, int A[N][M], int B[M][N]) {
    int i_c, j_c, i, j;
    int b_size = 16;
    for(i_c = 0;i < N;i_c += b_size) {
        for(j_c = 0;j_c < M;j_c += b_size) {
            for(i = i_c;i < i_c + b_size && i < N;++i) {
                for(j = j_c;j < j_c + b_size && j < M;++j) {
                    B[j][i] = A[i][j];
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

