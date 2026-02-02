file(GLOB SOURCES "src/*.cpp")

add_executable(day6_run ${SOURCES})

target_include_directories(day6_run PRIVATE include)