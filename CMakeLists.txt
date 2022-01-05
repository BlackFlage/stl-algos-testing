cmake_minimum_required(VERSION 3.5)

project(stl-algos)
set(CXX_STANDARD 20)

set(PROJECT_FILES
        src/main.cpp
        src/sorting.cpp
        src/LinkedList.h
        )

add_executable(${PROJECT_NAME} ${PROJECT_FILES})
add_executable(TESTS src/Tests.cpp)

add_subdirectory(vendor/googletest)
target_link_libraries(TESTS gtest gtest_main)
include_directories(${PROJECT_NAME} PRIVATE vendor/googletest/googletest/include)