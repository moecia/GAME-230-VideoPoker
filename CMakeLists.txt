cmake_minimum_required(VERSION 3.8)
project(GPM_230_VideoPoker)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Deck.cpp HandChecker.cpp VideoPoker.cpp)
add_executable(GPM_230_VideoPoker ${SOURCE_FILES})