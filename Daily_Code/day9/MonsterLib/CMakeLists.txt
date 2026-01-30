file(GLOB SOURCES "src/*.cpp")
# 创建动态库libMonsterLib.so
add_library(MonsterLib SHARED ${SOURCES})
# 链接后自动拥有访问include的权限
target_include_directories(MonsterLib PUBLIC include)