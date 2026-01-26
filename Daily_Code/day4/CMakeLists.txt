file(GLOB SOURCES "src/*.cpp")

add_executable(day4_run ${SOURCES})

target_include_directories(day4_run PRIVATE include)