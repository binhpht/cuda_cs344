#include "reduce.cuh"
#include <cstdlib>
#include <cuda_runtime_api.h>
#include <stdio.h>

int main(int argc, char **argv) {
	int deviceCount;
	cudaGetDeviceCount(&deviceCount);
	if (deviceCount == 0) {
		fprintf(stderr, "error: no devices supporting CUDA.\n");
		exit(EXIT_FAILURE);
	}
	int dev = 0;
	cudaSetDevice(dev);

	cudaDeviceProp devProps;
	if (cudaGetDeviceProperties(&devProps, dev) == 0)
	{
		printf("Using device %d:\n", dev);
		printf("%s; global mem: %dB; compute v%d.%d; clock: %d kHz\n",
		       devProps.name, (int)devProps.totalGlobalMem,
		       (int)devProps.major, (int)devProps.minor,
		       (int)devProps.clockRate);
	}

	const int ARRAY_SIZE = 1 << 20;
	const int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);

	// generate the input array on the host
	float h_in[ARRAY_SIZE];
	float sum = 0.0f;
	for(int i = 0; i < ARRAY_SIZE; i++) {
		// generate random float in [-1.0f, 1.0f]
		h_in[i] = -1.0f + (float)random()/((float)RAND_MAX/2.0f);
		sum += h_in[i];
	}

	// declare GPU memory pointers
	float * d_in, * d_intermediate, * d_out;

	// allocate GPU memory
	cudaMalloc((void **) &d_in, ARRAY_BYTES);
	cudaMalloc((void **) &d_intermediate, ARRAY_BYTES); // overallocated
	cudaMalloc((void **) &d_out, sizeof(float));

	// transfer the input array to the GPU
	cudaMemcpy(d_in, h_in, ARRAY_BYTES, cudaMemcpyHostToDevice);

	int whichKernel = 0;
	if (argc == 2) {
		whichKernel = atoi(argv[1]);
	}

	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	// launch the kernel
	switch(whichKernel) {
		case 0:
			printf("Running global reduce\n");
			cudaEventRecord(start, 0);
			for (int i = 0; i < 100; i++)
			{
				reduce(d_out, d_intermediate, d_in, ARRAY_SIZE, false);
			}
			cudaEventRecord(stop, 0);
			break;
		case 1:
			printf("Running reduce with shared mem\n");
			cudaEventRecord(start, 0);
			for (int i = 0; i < 100; i++)
			{
				reduce(d_out, d_intermediate, d_in, ARRAY_SIZE, true);
			}
			cudaEventRecord(stop, 0);
			break;
		default:
			fprintf(stderr, "error: ran no kernel\n");
			exit(EXIT_FAILURE);
	}
	cudaEventSynchronize(stop);
	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime, start, stop);
	elapsedTime /= 100.0f;      // 100 trials

	// copy back the sum from GPU
	float h_out;
	cudaMemcpy(&h_out, d_out, sizeof(float), cudaMemcpyDeviceToHost);

	printf("average time elapsed: %f\n", elapsedTime);

	// free GPU memory allocation
	cudaFree(d_in);
	cudaFree(d_intermediate);
	cudaFree(d_out);

	return 0;
}
