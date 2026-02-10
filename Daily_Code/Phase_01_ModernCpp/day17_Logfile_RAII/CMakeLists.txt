file(GLOB SOURCES "src/*.cpp")

add_executable(logfile ${SOURCES})

target_include_directories(logfile PRIVATE include)