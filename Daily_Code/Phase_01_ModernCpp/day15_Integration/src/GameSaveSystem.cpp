#include "GameSaveSystem.h"

bool GameSaveSystem::save(const std::string &filename, const PlayerRecord &player)
{
    // 以二进制形式打开文件
    std::ofstream outFile(filename, std::ios::binary | std::ios::trunc);
    if (!outFile)
    {
        std::cerr << "Open file Failed!" << std::endl;
        return false;
    }
    // 写入文件头
    outFile.write(reinterpret_cast<const char *>(&MAGIC_NUMBER), sizeof(MAGIC_NUMBER));
    outFile.write(reinterpret_cast<const char *>(&VERSION), sizeof(VERSION));

    // 写入固定长度数据
    outFile.write(reinterpret_cast<const char *>(&player.id), sizeof(player.id));
    outFile.write(reinterpret_cast<const char *>(&player.hp), sizeof(player.hp));
    outFile.write(reinterpret_cast<const char *>(&player.level), sizeof(player.level));
    outFile.write(reinterpret_cast<const char *>(&player.position), sizeof(player.position));

    // 写入长度变化数据
    size_t nameLen = player.name.size();
    // 先写入长度
    outFile.write(reinterpret_cast<const char *>(&nameLen), sizeof(nameLen));
    // 再写入内容
    outFile.write(player.name.data(), nameLen);

    std::cout << "[Save] File is Saved! " << filename << std::endl;
    return true;
}

bool GameSaveSystem::load(const std::string &filename, PlayerRecord &outplayer)
{
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile)
    {
        std::cerr << "File not found: " << filename << std::endl;
        return false;
    }

    // 校验文件头
    uint32_t magicNum = 0;
    uint16_t ver = 0;
    inFile.read(reinterpret_cast<char *>(&magicNum), sizeof(magicNum));
    inFile.read(reinterpret_cast<char *>(&ver), sizeof(ver));

    if (magicNum != MAGIC_NUMBER)
    {
        std::cerr << "[Error] Invalid file format! " << std::hex << magicNum << std::endl;
        return false;
    }
    if (ver > VERSION)
    {
        std::cerr << "[Error] File version Fault!" << std::endl;
        return false;
    }

    // 校验通过, 读取固定长度数据
    inFile.read(reinterpret_cast<char *>(&outplayer.id), sizeof(outplayer.id));
    inFile.read(reinterpret_cast<char *>(&outplayer.hp), sizeof(outplayer.hp));
    inFile.read(reinterpret_cast<char *>(&outplayer.level), sizeof(outplayer.level));
    inFile.read(reinterpret_cast<char *>(&outplayer.position), sizeof(outplayer.position));

    // 读取不固定数据
    size_t nameLen = 0;
    inFile.read(reinterpret_cast<char *>(&nameLen), sizeof(nameLen));
    // 根据读取的数据内容长度更新player内部数据长度
    outplayer.name.resize(nameLen);
    if (nameLen > 0)
    {
        // 读取内容放入name所在内存地址
        inFile.read(&outplayer.name[0], nameLen);
    }

    std::cout << "[Load] File is Loaded! " << std::endl;
    return true;
}