CMAKE_MINIMUM_REQUIRED(VERSION 3.18)
PROJECT(problem_set1 LANGUAGES CUDA CXX )

SET(CMAKE_CXX_STANDARD 14)
SET(ENABLE_PLATFORM_CUDA ON)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CXX_FLAGS "-stdlib=libstdc++")

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


ADD_EXECUTABLE(problem_set2 main.cpp)

TARGET_SOURCES(problem_set2 PRIVATE
               HW2.hpp
               HW2.cpp
               utils.hpp
               timer.hpp
               student_func.cu
               reference_calc.cpp
               reference_calc.hpp
               compare.cpp
               compare.hpp
               )
set_target_properties(problem_set2 PROPERTIES
                      CUDA_SEPARABLE_COMPILATION ON)
TARGET_LINK_LIBRARIES(problem_set2 CUDA::cudart CUDA::cuda_driver  ${OpenCV_LIBS})
