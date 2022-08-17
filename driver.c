#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "helper.h"
#include "kseq.h"
#include "align.h"
#include <zlib.h>

int main(int argc, char *argv[])
{
    struct timeval calc;
    double calctime;
    double gflops;
    float mem_bw;
    srand((unsigned)time(NULL));

    char* A;char* B; // sequence to be aligned A and B
    char* A_al;char* B_al; // aligned sequence A and B
    int match, mismatch, gap; // match, mismatch, gap penalty
    int A_len, B_len; // length of A and B
    
    int** M; // matrix for dynamic programming
    char** M_t; // matrix for traceback

    // read sequences from file
    if(argc < 3){
        printf("Insufficient arguments.\n");\
        return 0;
    }

    A = readFasta(argv[1]);
    B = readFasta(argv[2]);
    // printf("%s\n%s\n",A,B);

    A_len =  strlen(A);
    B_len =  strlen(B);

    // initialize matrices
    M = (int**)malloc(A_len*sizeof(int*));
    M_t = (char**)malloc(A_len*sizeof(char*));
    for(int i=0; i < A_len; ++i){
        M[i] = (int*)malloc(B_len*sizeof(int));
        M_t[i] = (char*)malloc(B_len*sizeof(char));
    }

    // set parameters
    match = -1;
    mismatch = 1;
    gap = 2;

    //initialize matrices
    for(int i=0; i < A_len; ++i){
        M[i][0] = gap*i;
    }
    for(int j=0; j < B_len; ++j){
        M[0][j] = gap*j;
    }

    tick(&calc);

    GlobalAlignment(A, B, A_len, B_len, match, mismatch, gap, M, M_t);

    calctime = tock(&calc);

    printf("score: %d\n",M[A_len-1][B_len-1]);
    printf("Time taken: %f\n",calctime);
    printf("score by checker: %d\n",checker(A,B,A_len,B_len,match,mismatch,gap,M,M_t));
    
}
