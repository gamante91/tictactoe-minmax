cmake_minimum_required(VERSION 2.4)

project(tictactoe-minimax)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-dangling-else")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(tictactoe-minimax board.cpp minmax.cpp play.cpp utilities.cpp)
