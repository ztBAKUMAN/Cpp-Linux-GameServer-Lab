cmake_minimum_required(VERSION 3.14)
project(Daily_Study)
# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 将生成的执行文件放入build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# 开启编译警告
add_compile_options(-Wall -Wextra)
# 添加子目录cmake文件
# add_subdirectory(day01_keywords)
# add_subdirectory(day02_use_smartptr)
# add_subdirectory(day03_use_move)
# add_subdirectory(day04_STL_algorithm)
# add_subdirectory(day05_header_cpp)
# add_subdirectory(day06_virtualclass)
# add_subdirectory(day07_cmake_library)
# add_subdirectory(day08_RuleOfFive)
# add_subdirectory(day09_PImpl)
# add_subdirectory(day10_more_algorithm)
# add_subdirectory(day11_file_IO)
# add_subdirectory(day12_FileSystem)
# add_subdirectory(day13_JSON)
add_subdirectory(day14_CfgManager)