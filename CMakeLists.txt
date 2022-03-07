cmake_minimum_required(VERSION 3.0)

enable_language(CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)


project(ITCHI  VERSION 1.0)
# //set(CMAKE_BUILD_TYPE "Debug")
message("-----------------------------------------------------------------------------------------------------------------------------------")

message("PROJECT_NAME:${PROJECT_NAME}")

message("PROJECT_VERSION:${PROJECT_VERSION}")

message("PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR}")

message("PROJECT_BINARY_DIR:${PROJECT_BINARY_DIR}")


SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

if(PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
    message(FATAL "PROJECT_BINARY_DIR can not be the same as PROJECT_SOURCE_DIR")
endif()

if(NOT CMAKE_BUILD_TYPE)
    message( "-----------------------DEFAULT BUILD TYPE Release-----------------------------")
    set(CMAKE_BUILD_TYPE Release)
else()
    message( "-----------------------BUILD TYPE is ${CMAKE_BUILD_TYPE}-----------------------------")
    if(${CMAKE_BUILD_TYPE} STREQUAL “Debug”)
    add_definitions("-Wall -g")
    endif()
endif()

# set(CMAKE_CXX_FLAGS 

#     -std=c++11 )

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

#base库文件
add_subdirectory(./src/Base)
#net库文件
add_subdirectory(./src/Net)

#可执行文件
add_subdirectory(./test)




#target_include_directories(config ${PROJECT_BINARY_DIR}/include)



