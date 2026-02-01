#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

/* 定义数据结构 */
struct Vec3 {
    float x;
    float y;
    float z;
};

// 玩家数据对象
class PlayerRecord {
public:
    uint64_t id;
    int32_t hp;
    int32_t level;
    Vec3 position;
    std::string name;

    void printInfo() {
        std::cout << "[Player ID: " << id << "] " 
                  << name << " (Lv." << level << ") "
                  << "HP: " << hp 
                  << " Position: (" << position.x << ", " 
                  << position.y << ", " << position.z << ")" << std::endl;
    }
};

/* 序列化工具 */
class GameSaveSystem {
    // MagicNumber校验数据是否合法
    // static const + 整型，可以类内声明并初始化，但不能取地址
    // static const + 非整型，C++17之前不能在类内初始化，需要使用类内声明+类外初始化; C++17之后加上inline允许在类内初始化
    // static const uint32_t MAGIC_NUMBER = 0x534F554C;

    // 现代C++写法: 定义整型/浮点/简单数值，使用static constexpr
    // 定义复杂对象，使用static inline const
    // 定义校验符
    static constexpr uint32_t MAGIC_NUMBER = 0x534F554C;
    // 定义版本号
    static constexpr uint16_t VERSION = 1;

public:
    // 保存文件
    static bool save(const std::string& filename, const PlayerRecord& player)
    {
        // 以二进制形式打开文件
        std::ofstream outFile(filename, std::ios::binary | std::ios::trunc);
        if(!outFile)
        {
            std::cerr << "Open file Failed!" << std::endl;
            return false;
        }
        // 写入文件头
        outFile.write(reinterpret_cast<const char*>(&MAGIC_NUMBER), sizeof(MAGIC_NUMBER));
        outFile.write(reinterpret_cast<const char*>(&VERSION), sizeof(VERSION));

        // 写入固定长度数据
        outFile.write(reinterpret_cast<const char*>(&player.id), sizeof(player.id));
        outFile.write(reinterpret_cast<const char*>(&player.hp), sizeof(player.hp));
        outFile.write(reinterpret_cast<const char*>(&player.level), sizeof(player.level));
        outFile.write(reinterpret_cast<const char*>(&player.position), sizeof(player.position));

        // 写入长度变化数据
        size_t nameLen = player.name.size();
        // 先写入长度
        outFile.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
        // 再写入内容
        outFile.write(player.name.data(), nameLen);

        std::cout << "[Save] File is Saved! " << filename << std::endl;
        return true;
    }

    // 读取
    static bool load(const std::string& filename, PlayerRecord& outplayer)
    {
        std::ifstream inFile(filename, std::ios::binary);
        if(!inFile)
        {
            std::cerr << "File not found: " << filename << std::endl;
            return false;
        }

        // 校验文件头
        uint32_t magicNum = 0;
        uint16_t ver = 0;
        inFile.read(reinterpret_cast<char*>(&magicNum), sizeof(magicNum));
        inFile.read(reinterpret_cast<char*>(&ver), sizeof(ver));

        if(magicNum != MAGIC_NUMBER)
        {
            std::cerr << "[Error] Invalid file format! " << std::hex << magicNum << std::endl;
            return false;
        }
        if(ver > VERSION)
        {
            std::cerr << "[Error] File version Fault!" << std::endl;
            return false;
        }

        // 校验通过, 读取固定长度数据
        inFile.read(reinterpret_cast<char*>(&outplayer.id), sizeof(outplayer.id));
        inFile.read(reinterpret_cast<char*>(&outplayer.hp), sizeof(outplayer.hp));
        inFile.read(reinterpret_cast<char*>(&outplayer.level), sizeof(outplayer.level));
        inFile.read(reinterpret_cast<char*>(&outplayer.position), sizeof(outplayer.position));

        // 读取不固定数据
        size_t nameLen = 0;
        inFile.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
        // 根据读取的数据内容长度更新player内部数据长度
        outplayer.name.resize(nameLen);
        if(nameLen > 0)
        {
            // 读取内容放入name所在内存地址
            inFile.read(&outplayer.name[0], nameLen);
        }

        std::cout << "[Load] File is Loaded! " << std::endl;
        return true;
    }
    
};

int main()
{
    // 模拟
    PlayerRecord myActor;
    myActor.id = 47;
    myActor.hp = 100;
    myActor.level = 10;
    myActor.position = { 50.0f, 20.0f, 100.0f };
    myActor.name = "Alex";

    // 原始数据
    std::cout << "--originData--" << std::endl;
    myActor.printInfo();
    GameSaveSystem::save("savedata.dat", myActor);

    PlayerRecord newActor;
    std::cout << "--loadingData--" << std::endl;
    if(GameSaveSystem::load("savedata.dat", newActor))
    {
        newActor.printInfo();
        if(newActor.name == myActor.name && newActor.id == myActor.id)
        {
            std::cout << "Serialization vertified!" << std::endl;
        }
        else
        {
            std::cout << "Data miss!" << std::endl;
        }
    }
    return 0;
}