#include "ConfigManager.h"
auto& ConfigMng = ConfigManager::getInstance();
int main()
{
    // 注意使用const不发生拷贝
    const auto& config = ConfigMng.getConfig();
    // 打印验证
    std::cout << "=== Server Configuration ===" << std::endl;
    std::cout << "Ip : " << config.ip << std::endl;
    std::cout << "Port : " << config.port << std::endl;
    std::cout << "PVP  : " << (config.pvp ? "ON" : "OFF") << std::endl;
    std::cout << "Login: ";
    for (int id : config.loginID) {
        std::cout << id << " ";
    }
    std::cout << "\n============================" << std::endl;
    return 0;
}