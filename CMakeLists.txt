cmake_minimum_required(VERSION 3.21)
project(SysPro_5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(sources)

add_executable(SysPro_5
        sources/OrgChart.cpp
        sources/OrgChart.hpp
        Demo.cpp
        Test.cpp
        doctest.h
        TestCounter.cpp)
