cmake_minimum_required(VERSION 3.8)
project(robotics_gtest_extension)
set(CMAKE_CXX_STANDARD 17)

include_directories(src include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#file(GLOB_RECURSE LIB_ROBOTICS_GTEST_EXTENSION src/*.cpp src/*.hpp)
#add_library(${PROJECT_NAME} STATIC ${LIB_ROBOTICS_GTEST_EXTENSION})

