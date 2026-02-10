file(GLOB SOURCES "src/*.cpp")

add_executable(RAII ${SOURCES})

target_include_directories(RAII PRIVATE include)