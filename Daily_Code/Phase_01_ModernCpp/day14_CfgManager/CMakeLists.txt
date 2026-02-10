# 自动拉取并链接库
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

file(GLOB SOURCES "src/*.cpp")

add_executable(manager ${SOURCES})

target_include_directories(manager PRIVATE include)
target_link_libraries(manager PRIVATE nlohmann_json::nlohmann_json)