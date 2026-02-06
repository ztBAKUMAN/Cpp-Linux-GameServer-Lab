#include <iostream>
#include <filesystem>
#include <vector>
#include "ConfigManager.h"
#include "GameSaveSystem.h"

namespace fs = std::filesystem;
auto &GLOBALCOF = ConfigManager::getInstance();

int main()
{
    // 1.加载系统配置
    std::cout << "[Boot] Loading Configuration..." << std::endl;
    if (!GLOBALCOF.loadConfig())
    {
        std::cerr << "[Fatal] Config load failed!" << std::endl;
        return 1;
    }

    // 获取配置数据并打印
    const auto &cfg = GLOBALCOF.getConfig();
    std::cout << "[Boot] Server Configuration: " << std::endl;
    std::cout << "Ip : " << cfg.ip << std::endl;
    std::cout << "Port : " << cfg.port << std::endl;
    std::cout << "PVP  : " << (cfg.pvp ? "ON" : "OFF") << std::endl;
    std::cout << "Login: ";
    for (int id : cfg.loginID)
    {
        std::cout << id << " ";
    }
    std::cout << "\n============================" << std::endl;

    // 2.加载玩家存档
    std::string savePath = "Saves";
    // 不存在目录则新建
    if (!fs::exists(savePath))
    {
        fs::create_directory(savePath);
        // 创建一些默认存档文件做测试
        PlayerRecord record;
        record.id = 1;
        record.hp = 100;
        record.level = 10;
        record.position = {50.0f, 20.0f, 100.0f};
        record.name = "Alex";

        GameSaveSystem::save("savedata01.dat", record);
        PlayerRecord record2(record);
        record2.id = 2;
        GameSaveSystem::save("savedata02.dat", record2);
        // 创建错误文档
        std::ofstream(savePath + "/test.dat") << "test";
    }

    // 扫描文件夹下文件
    std::cout << "[System] Scanning saves in '" << savePath << "'..." << std::endl;
    int count = 0;
    for(const auto& data : fs::directory_iterator(savePath))
    {
        if(data.is_regular_file() && data.path().extension() == ".dat")
        {
            std::string filepath = data.path().string();
            std::cout << "->Loading " << data.path().filename().string() << "..." << std::endl;
            PlayerRecord record;
            if(GameSaveSystem::load(filepath, record))
            {
                // 加载文档成功
                std::cout << "[OK] [Player ID: " << record.id << "] " 
                  << record.name << " (Lv." << record.level << ") "
                  << "HP: " << record.hp 
                  << " Position: (" << record.position.x << ", " 
                  << record.position.y << ", " << record.position.z << ")" << std::endl;
                count++;
            }
            else{
                // 加载文档失败
                std::cout << "[Error] Corrupted file: " << filepath << std::endl;
            }
        }
    }
    // 服务器已就绪
    std::cout << "[System] Server Ready. " << count << " players loaded." << std::endl;
    return 0;
}