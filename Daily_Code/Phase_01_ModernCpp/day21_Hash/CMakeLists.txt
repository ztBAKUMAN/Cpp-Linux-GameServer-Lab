file(GLOB SOURCES "src/*.cpp")

add_executable(hash ${SOURCES})

target_include_directories(hash PRIVATE include)