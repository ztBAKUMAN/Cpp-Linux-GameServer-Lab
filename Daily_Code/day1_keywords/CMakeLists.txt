file(GLOB SOURCES "src/*.cpp")

add_executable(day1_run ${SOURCES})

target_include_directories(day1_run PRIVATE include)