cmake_minimum_required(VERSION 3.10)
project(Daily_Study)
# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 将生成的执行文件放入build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# 开启编译警告
add_compile_options(-Wall -Wextra)
# 添加子目录cmake文件
# add_subdirectory(day1)
# add_subdirectory(day2)
# add_subdirectory(day3)
# add_subdirectory(day4)
# add_subdirectory(day5)
# add_subdirectory(day6)
# add_subdirectory(day7)
add_subdirectory(day11)