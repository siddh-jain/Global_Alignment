#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void GlobalAlignment(char *A, char *B, int A_len, int B_len, int match, int mismatch, int gap, int **M, char **M_t)
{
    // fill matrices
    //  for(int i=1; i < A_len; ++i){
    //      for(int j=1; j < B_len; ++j){
    //          int score_diag = M[i-1][j-1] + (A[i] == B[j] ? match : mismatch);
    //          int score_left = M[i-1][j] + gap;
    //          int score_up = M[i][j-1] + gap;
    //          if(score_diag <= score_left && score_diag <= score_up)
    //              M[i][j] = score_diag;
    //          else if(score_left <= score_up && score_left <= score_diag)
    //              M[i][j] = score_left;
    //          else if(score_up <= score_left && score_up <= score_diag)
    //              M[i][j] = score_up;
    //          // printf("%d ",M[i][j]);
    //      }
    //  }

    // column wise dynamic programming /////////////////
    for (int j = 1; j < B_len; ++j)
    {
        for (int i = 1; i < A_len; ++i)
        {
            int score_diag = M[i - 1][j - 1] + (A[i] == B[j] ? match : mismatch);
            int score_left = M[i - 1][j] + gap;
            int score_up = M[i][j - 1] + gap;
            if (score_diag <= score_left && score_diag <= score_up)
                M[i][j] = score_diag;
            else if (score_left <= score_up && score_left <= score_diag)
                M[i][j] = score_left;
            else if (score_up <= score_left && score_up <= score_diag)
                M[i][j] = score_up;
            // printf("%d ",M[i][j]);
        }
    }

    // // row wise dynamic programming //////////////////
    // for (int i = 1; i < A_len; ++i)
    // {
    //     for (int j = 1; j < B_len; ++j)
    //     {
    //         int score_diag = M[i - 1][j - 1] + (A[i] == B[j] ? match : mismatch);
    //         int score_left = M[i - 1][j] + gap;
    //         int score_up = M[i][j - 1] + gap;
    //         if (score_diag <= score_left && score_diag <= score_up)
    //             M[i][j] = score_diag;
    //         else if (score_left <= score_up && score_left <= score_diag)
    //             M[i][j] = score_left;
    //         else if (score_up <= score_left && score_up <= score_diag)
    //             M[i][j] = score_up;
    //         // printf("%d ",M[i][j]);
    //     }
    // }

    // // diagonally parallelise //////////////////
    //     for (int k = 2; k < A_len + B_len - 1; k++)
    //     {
    // #pragma omp parallel for
    //         for (int i = 1; i < k; i++)
    //         {
    //             if (i >= A_len)
    //             {
    //                 continue;
    //             }
    //             int j = k - i;
    //             if (j >= B_len)
    //             {
    //                 continue;
    //             }
    //             int score_diag = M[i - 1][j - 1] + (A[i] == B[j] ? match : mismatch);
    //             int score_left = M[i - 1][j] + gap;
    //             int score_up = M[i][j - 1] + gap;
    //             if (score_diag <= score_left && score_diag <= score_up)
    //                 M[i][j] = score_diag;
    //             else if (score_left <= score_up && score_left <= score_diag)
    //                 M[i][j] = score_left;
    //             else if (score_up <= score_left && score_up <= score_diag)
    //                 M[i][j] = score_up;
    //         }
    //     }

//     // tiling parallelisation - row wise //////////////////
//     int tile_len = 100;
//     int p_len = ceil(A_len / (double)tile_len);
//     int q_len = ceil(B_len / (double)tile_len);
//     for (int r = 0; r < p_len + q_len - 1; r++)
//     {
// #pragma omp parallel for
//         for (int p = 0; p <= r; p++)
//         {
//             if (p >= p_len)
//             {
//                 continue;
//             }
//             int q = r - p;
//             if (q >= q_len)
//             {
//                 continue;
//             }
//             // row wise
//             for (int i = p * tile_len; i < (p + 1) * tile_len; i++)
//             {
//                 if (i >= A_len || i == 0)
//                 {
//                     continue;
//                 }
//                 for (int j = q * tile_len; j < (q + 1) * tile_len; j++)
//                 {
//                     if (j >= B_len || j == 0)
//                     {
//                         continue;
//                     }
//                     int score_diag = M[i - 1][j - 1] + (A[i] == B[j] ? match : mismatch);
//                     int score_left = M[i - 1][j] + gap;
//                     int score_up = M[i][j - 1] + gap;
//                     if (score_diag <= score_left && score_diag <= score_up)
//                         M[i][j] = score_diag;
//                     else if (score_left <= score_up && score_left <= score_diag)
//                         M[i][j] = score_left;
//                     else if (score_up <= score_left && score_up <= score_diag)
//                         M[i][j] = score_up;
//                     // printf("%d ", M[i][j]);
//                 }
//             }
//         }
//     }

    // // tiling parallelisation - diagonally //////////////////
    //     int tile_len = 250;
    //     int p_len = ceil(A_len / (double)tile_len);
    //     int q_len = ceil(B_len / (double)tile_len);
    //     for (int r = 0; r < p_len + q_len - 1; r++)
    //     {
    // #pragma omp parallel for
    //         for (int p = 0; p <= r; p++)
    //         {
    //             if (p >= p_len)
    //             {
    //                 continue;
    //             }
    //             int q = r - p;
    //             if (q >= q_len)
    //             {
    //                 continue;
    //             }
    //             //diagonally
    //             for (int k = 0; k < 2*tile_len - 1; k++)
    //             {
    //         #pragma omp parallel for
    //                 for (int i = p*tile_len; i < (p+1)*tile_len; i++)
    //                 {
    //                     if (i >= A_len || i == 0)
    //                     {
    //                         continue;
    //                     }
    //                     int j = q*tile_len+ k - (i-p*tile_len);
    //                     if (j >= B_len || j==0)
    //                     {
    //                         continue;
    //                     }
    //                     int score_diag = M[i - 1][j - 1] + (A[i] == B[j] ? match : mismatch);
    //                     int score_left = M[i - 1][j] + gap;
    //                     int score_up = M[i][j - 1] + gap;
    //                     if (score_diag <= score_left && score_diag <= score_up)
    //                         M[i][j] = score_diag;
    //                     else if (score_left <= score_up && score_left <= score_diag)
    //                         M[i][j] = score_left;
    //                     else if (score_up <= score_left && score_up <= score_diag)
    //                         M[i][j] = score_up;
    //                 }
    //             }
    //         }
    //     }

    // traceback
    // int i = A_len - 1;
    // int j = B_len - 1;
    // while (i > 0 && j > 0)
    // {
    //     if (M[i][j] == M[i - 1][j - 1] + (A[i] == B[j] ? match : mismatch))
    //     {
    //         M_t[i][j] = '\\';
    //         i--;
    //         j--;
    //     }
    //     else if (M[i][j] == M[i - 1][j] + gap)
    //     {
    //         M_t[i][j] = '|';
    //         i--;
    //     }
    //     else if (M[i][j] == M[i][j - 1] + gap)
    //     {
    //         M_t[i][j] = '-';
    //         j--;
    //     }
    // }
}

int checker(char *A, char *B, int A_len, int B_len, int match, int mismatch, int gap, int **M, char **M_t)
{
    // fill matrices
    for (int i = 1; i < A_len; ++i)
    {
        for (int j = 1; j < B_len; ++j)
        {
            int score_diag = M[i - 1][j - 1] + (A[i] == B[j] ? match : mismatch);
            int score_left = M[i - 1][j] + gap;
            int score_up = M[i][j - 1] + gap;
            if (score_diag <= score_left && score_diag <= score_up)
                M[i][j] = score_diag;
            else if (score_left <= score_up && score_left <= score_diag)
                M[i][j] = score_left;
            else if (score_up <= score_left && score_up <= score_diag)
                M[i][j] = score_up;
            // printf("%d ",M[i][j]);
        }
    }
    return M[A_len - 1][B_len - 1];
}