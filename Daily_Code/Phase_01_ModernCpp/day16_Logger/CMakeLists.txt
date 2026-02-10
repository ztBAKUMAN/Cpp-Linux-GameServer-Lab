file(GLOB SOURCES "src/*.cpp")

add_executable(logger ${SOURCES})

target_include_directories(logger PRIVATE include)