file(GLOB SOURCES "src/*.cpp")

add_executable(moveSemantics ${SOURCES})

target_include_directories(hmoveSemanticsh PRIVATE include)