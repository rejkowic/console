cmake_minimum_required(VERSION 3.9)

project(console-test)

add_subdirectory(app-factory)

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} console-test.cpp)
target_link_libraries(${PROJECT_NAME} console app-factory)
