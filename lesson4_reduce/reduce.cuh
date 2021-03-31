
#ifndef CUDA_CS344_REDUCE_CUH
#define CUDA_CS344_SQUARE_CUH
#include <cuda_runtime_api.h>


__global__ void global_reduce_kernel(float * d_out, float * d_in);

__global__ void shmem_reduce_kernel(float * d_out, const float * d_in);
void reduce(float * d_out, float * d_intermediate, float * d_in,
            int size, bool usesSharedMemory);
#endif//CUDA_CS344_REDUCE_CUH
