cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0025 NEW)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

project(VRHelloWorld)
ADD_DEFINITIONS(
    -std=c++11 
    -stdlib=libc++
)
add_subdirectory(source)
set(LIBRARY_PATH "Not Defined" CACHE PATH "Path to external libraries, like Leap")

