cmake_minimum_required(VERSION 3.31)
project(findCounterExamples LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(GeneUtils STATIC lib/GeneUtils.cpp lib/ThreadPool.cpp)

add_executable(main src/main.cpp src/Solution.cpp)

target_link_libraries(main PUBLIC GeneUtils)