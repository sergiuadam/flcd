cmake_minimum_required(VERSION 3.17)
project(SymbolTable)

set(CMAKE_CXX_STANDARD 17)

add_executable(SymbolTable main.cpp PIF.cpp PIF.h FileManager.cpp SymbolTable.cpp SymbolTable.h)