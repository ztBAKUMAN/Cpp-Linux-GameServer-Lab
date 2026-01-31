add_executable(GameApp main.cpp)
# 链接动态库
target_link_libraries(GameApp PRIVATE MonsterLib)