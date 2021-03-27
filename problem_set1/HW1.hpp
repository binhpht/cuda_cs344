//
// Created by binhpht on 27.3.2021.
//
#ifndef CUDA_CS344_HW1_HPP
#define CUDA_CS344_HW1_HPP

#include <string>
#include <vector_types.h>
size_t numRows() ;
size_t numCols() ;

//return types are void since any internal error will be handled by quitting
//no point in returning error codes...
//returns a pointer to an RGBA version of the input image
//and a pointer to the single channel grey-scale output
//on both the host and device
void preProcess(uchar4 **inputImage, unsigned char **greyImage,
                uchar4 **d_rgbaImage, unsigned char **d_greyImage,
                const std::string &filename);

void postProcess(const std::string &output_file, unsigned char *data_ptr);

void cleanup();

void generateReferenceImage(std::string input_filename, std::string output_filename);


#endif//CUDA_CS344_HW1_HPP
