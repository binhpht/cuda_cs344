//
// Created by binhpht on 27.3.2021.
//
#include <stdio.h>
#include "iostream"

#include "square.cuh"
__global__ void square (float * d_out, float * d_in) {
//	int idx = threadIdx.x;
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	float f = d_in[idx];
	d_out[idx] = f * f;
}
void call_square (int thread_num, float * d_out, float * d_in) {
	::square<<<8,8>>>(d_out, d_in);

}