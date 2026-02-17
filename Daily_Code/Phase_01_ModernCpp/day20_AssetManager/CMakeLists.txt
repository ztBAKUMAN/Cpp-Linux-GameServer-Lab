file(GLOB SOURCES "src/*.cpp")

add_executable(assetmanager ${SOURCES})

target_include_directories(assetmanager PRIVATE include)