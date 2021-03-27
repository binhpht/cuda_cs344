//
// Created by binhpht on 27.3.2021.
//

#ifndef CUDA_CS344_SQUARE_CUH
#define CUDA_CS344_SQUARE_CUH


__global__ void square (float * d_out, float * d_in);
void call_square (int thread_num, float * d_out, float * d_in) ;

#endif//CUDA_CS344_SQUARE_CUH
