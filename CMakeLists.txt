cmake_minimum_required(VERSION 3.20)
project(THW)

set(CMAKE_CXX_STANDARD 14)

add_executable(THW main.cpp sorts/sorts.cpp sorts/sorts.hpp TestDataset.cpp TestDataset.hpp)
