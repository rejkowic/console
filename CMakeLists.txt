cmake_minimum_required(VERSION 3.9)

project(console)

if (CMAKE_CURRENT_SOURCE_DIR EQUAL CMAKE_SOURCE_DIR)
  add_subdirectory(test)
endif()

set(CMAKE_CXX_STANDARD 17)
add_library(${PROJECT_NAME} src/Console.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC interface)
