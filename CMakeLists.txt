cmake_minimum_required(VERSION 3.1)

#set the project name and version
project(HW_4 VERSION 1.0)

find_package(OpenCV REQUIRED)

#specify the c++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${OpenCV_INCLUDE_DIRS})

add_library(HW4_libs src/img_process.cpp)
add_library(HW4_libs2 src/VideoReader.cpp)

#add the executable
add_executable(HW4 apps/HW4.cpp) 


target_link_libraries(HW4 ${OpenCV_LIBS})
target_link_libraries(HW4 HW4_libs)
target_link_libraries(HW4 HW4_libs2)