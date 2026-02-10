# 自动拉取并链接库
include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

file(GLOB SOURCES "./*.cpp")

add_executable(json_test ${SOURCES})

target_link_libraries(json_test PRIVATE nlohmann_json::nlohmann_json)