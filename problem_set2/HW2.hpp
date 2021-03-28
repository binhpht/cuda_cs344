//
// Created by binhpht on 27.3.2021.
//
#ifndef CUDA_CS344_HW2_HPP
#define CUDA_CS344_HW2_HPP

#include <string>
#include <vector_types.h>
size_t numRows() ;
size_t numCols() ;

uchar4 * get_d_inputImageRGBA();
uchar4 * get_d_outputImageRGBA();

//return types are void since any internal error will be handled by quitting
//no point in returning error codes...
//returns a pointer to an RGBA version of the input image
//and a pointer to the single channel grey-scale output
//on both the host and device
void preProcess(uchar4 **h_inputImageRGBA, uchar4 **h_outputImageRGBA,
                uchar4 **d_inputImageRGBA, uchar4 **d_outputImageRGBA,
                unsigned char **d_redBlurred,
                unsigned char **d_greenBlurred,
                unsigned char **d_blueBlurred,
                float **h_filter, int *filterWidth,
                const std::string &filename);

void postProcess(const std::string& output_file, uchar4* data_ptr);
void cleanUp();

void generateReferenceImage(std::string input_file, std::string reference_file, int kernel_size);

#endif//CUDA_CS344_HW2_HPP
