CMAKE_MINIMUM_REQUIRED(VERSION 3.18)
PROJECT(reduce_lesson4 )

SET(CMAKE_CXX_STANDARD 14)
SET(ENABLE_PLATFORM_CUDA ON)
IF (ENABLE_PLATFORM_CUDA)
	# If not specified otherwise:
	# Include PTX code for compute capability 6.1 or greater (virtual).
	# Include precompiled binaries for 1060, 1080 (sm_61) (real).
	IF (NOT CMAKE_CUDA_ARCHITECTURES)
		SET(CMAKE_CUDA_ARCHITECTURES "61")
		MESSAGE(STATUS "CMAKE_CUDA_ARCHITECTURES not specified, defaulting to: ${CMAKE_CUDA_ARCHITECTURES}.")
	ENDIF ()
	ENABLE_LANGUAGE(CUDA)
	FIND_PACKAGE(CUDAToolkit 9 REQUIRED)
	# Add CUDA device debug symbols, but only in debug mode.
	ADD_COMPILE_OPTIONS("$<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CUDA>>:-G>")
ENDIF ()


ADD_EXECUTABLE(reduce_lesson4 main.cpp)

TARGET_SOURCES(reduce_lesson4 PRIVATE
               reduce.cuh
               reduce.cu
               )
set_target_properties(reduce_lesson4 PROPERTIES
                      CUDA_SEPARABLE_COMPILATION ON)
TARGET_LINK_LIBRARIES(reduce_lesson4 CUDA::cudart CUDA::cuda_driver)
