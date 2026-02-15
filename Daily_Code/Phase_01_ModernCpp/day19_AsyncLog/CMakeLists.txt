file(GLOB SOURCES "src/*.cpp")

add_executable(asynclog ${SOURCES})

target_include_directories(asynclog PRIVATE include)