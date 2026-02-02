
file(GLOB SOURCES "src/*.cpp")

add_executable(day2_run ${SOURCES})

target_include_directories(day2_run PRIVATE include)