file(GLOB SOURCES "./*.cpp")

add_executable(fileSystem ${SOURCES})

# target_include_directories(fileSystem PRIVATE include)