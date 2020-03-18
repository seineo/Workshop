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
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
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
 * trans_simple_blocking - A transpose function based on simple blocking
 */
char trans_simple_blocking_desc[] = "Simple blocking scan transpose";
void trans_simple_blocking(int M, int N, int A[N][M], int B[M][N]) {
    /*
     * Along the diagonal(4 blocks),each block has 8*2 + 8 + 7*2 = 38 misses.
     * In other blocks, each has 8 + 8 = 16 misses. In total, 4*38 + 12*16
     * = 344 misses
     */
    int i_c, j_c, i, j;
    int b_size = 8;
    //control loops
    for(i_c = 0;i_c < N;i_c += b_size) {
        for(j_c = 0;j_c < M;j_c += b_size) {
            //block manipulations
            for(i = i_c;i < i_c + b_size;++i) {
                for(j = j_c;j < j_c + b_size;++j) {
                    B[j][i] = A[i][j];
                }
            }
        }
    }
}

char trans_copy_desc[] = "Copy transpose";
void trans_copy(int M, int N, int A[N][M], int B[M][N]) {
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
    registerTransFunction(trans, trans_desc); 
    registerTransFunction(trans_simple_blocking, trans_simple_blocking_desc);
    registerTransFunction(trans_copy, trans_copy_desc);
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

