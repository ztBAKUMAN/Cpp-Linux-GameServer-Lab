# CMake生成动态库并调用

cmake_minimum_required(VERSION 3.10)
project(Day7_Make_SharedLib)

set(CMAKE_CXX_STANDARD 17)

# 执行程序生成路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# 库生成路径
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 添加子目录
add_subdirectory(MonsterLib)
add_subdirectory(Game)