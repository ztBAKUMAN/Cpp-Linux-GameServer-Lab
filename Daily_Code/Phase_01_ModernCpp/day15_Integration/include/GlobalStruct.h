#pragma once
#include <string>
#include <vector>

// 配置文件结构体
struct JsonConfig{
    std::string ip;
    int port;
    int maxPlayer;
    bool pvp;
    std::vector<int> loginID;
};

// 位置数据
struct Vec3 {
    float x;
    float y;
    float z;
};

// 玩家数据
struct PlayerRecord {
public:
    uint64_t id;
    int32_t hp;
    int32_t level;
    Vec3 position;
    std::string name;
};