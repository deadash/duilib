cmake_minimum_required(VERSION 3.15)

project(dui)

message(STATUS," CMake project files for duilib")

add_definitions(-DUNICODE -D_UNICODE)

add_subdirectory(duilib)
