#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include "GlobalStruct.h"

/* 序列化工具 */
class GameSaveSystem {
    // MagicNumber校验数据是否合法
    // 定义校验符
    static constexpr uint32_t MAGIC_NUMBER = 0x534F554C;
    // 定义版本号
    static constexpr uint16_t VERSION = 1;

public:
    // 保存文件
    static bool save(const std::string& filename, const PlayerRecord& player);

    // 读取
    static bool load(const std::string& filename, PlayerRecord& outplayer);
    
};
