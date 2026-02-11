file(GLOB SOURCES "src/*.cpp")

add_executable(timer ${SOURCES})

target_include_directories(timer PRIVATE include)