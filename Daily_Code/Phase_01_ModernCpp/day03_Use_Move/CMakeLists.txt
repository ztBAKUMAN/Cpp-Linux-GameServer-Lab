file(GLOB SOURCES "src/*.cpp")

add_executable(day3_run ${SOURCES})

target_include_directories(day3_run PRIVATE include)