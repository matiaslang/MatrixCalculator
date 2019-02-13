cmake_minimum_required(VERSION 3.12)
project(vt6_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(vt6 ConcreteSquareMatrix.cpp SymbolicSquareMatrix.cpp IntElement.cpp VarElement.cpp Element.cpp CompositeElement.cpp)