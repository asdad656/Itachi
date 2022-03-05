cmake_minimum_required(VERSION 3.0)

project(ITCHI VERSION 1.0)

# //set(CMAKE_BUILD_TYPE "Debug")


set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
add_definitions("-Wall -g")

# set(CMAKE_CXX_FLAGS 
#     -std=c++11 )

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#base库文件
add_subdirectory(./src/Base)
#可执行文件
add_subdirectory(./test)




#target_include_directories(config ${PROJECT_BINARY_DIR}/include)



