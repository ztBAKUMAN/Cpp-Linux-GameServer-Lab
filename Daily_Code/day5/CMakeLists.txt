file(GLOB SOURCES "src/*.cpp")

add_executable(day5_run ${SOURCES})

target_include_directories(day5_run PRIVATE include)