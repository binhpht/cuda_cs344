#include <stdio.h>
#include <cuda_runtime_api.h>
#include "square.cuh"

int main() {
	const int ARRAY_SIZE = 64;
	const int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);
	float h_in[ARRAY_SIZE];
	float h_out[ARRAY_SIZE];
	float *d_in;
	float *d_out;
	for (int i = 0 ; i < ARRAY_SIZE; i ++) {
		h_in[i] = float(i);
	}
	cudaMalloc((void **) &d_in, ARRAY_BYTES);
	cudaMalloc((void **) &d_out, ARRAY_BYTES);
	cudaMemcpy(d_in,h_in,ARRAY_BYTES,cudaMemcpyHostToDevice);
	call_square(ARRAY_SIZE,d_out,d_in);
	cudaDeviceSynchronize();
	cudaMemcpy(h_out, d_out, ARRAY_BYTES, cudaMemcpyDeviceToHost);

	for (int i = 0 ; i < ARRAY_SIZE; i ++) {
		printf("%f", h_out[i]);
		printf(((i % 4) != 3) ? "\t" : "\n");

	}
	cudaFree(d_in);
	cudaFree(d_out);
	return 0;
}
