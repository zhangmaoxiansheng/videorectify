cmake_minimum_required (VERSION 3.10) 
set(name ImageRectify)
project (${name})
set(CMAKE_CXX_FLAG "${CMAKE_CXX_FLAG} -std=c++11")
FIND_PACKAGE(OpenCV REQUIRED)
find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})

add_executable(${name} 
	StereoRectify.h		
	StereoRectify.cpp 
	main.cpp )
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
 
