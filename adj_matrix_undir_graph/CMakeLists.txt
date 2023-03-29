cmake_minimum_required(VERSION 3.24)
project(adj_matrix_undir_graph)

set(CMAKE_CXX_STANDARD 11)

add_executable(adj_matrix_undir_graph TestAdjMatrixUndirGraph.cpp Assistance.h AdjMatrixUndirGraph.h)
