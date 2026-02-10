#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

// 设置nlohmann::json类的简称
using json = nlohmann::json;

// 配置文件结构体
struct JsonConfig{
    std::string ip;
    int port;
    int maxPlayer;
    bool pvp;
    std::vector<int> loginID;
};

bool Config2Json(const JsonConfig& config, json& json)
{
    try{
        json["ip"] = config.ip;
        json["port"] = config.port;
        json["max_player"] = config.maxPlayer;
        json["features"]["enable_pvp"] = config.pvp;
        for(auto num : config.loginID)
        {
            json["login_ids"].push_back(num);
        }
    }catch(const json::type_error& e)
    {
        std::cerr << "Type Error!" << e.what() << std::endl;
        return false;
    }
    return true;
}

bool Json2Config(const json& j, JsonConfig& config)
{
    try{
        config.ip = j["ip"];
        config.port = j["port"];
        config.maxPlayer = j["max_player"];
        config.pvp = j["features"]["enable_pvp"];
        config.loginID = j["login_ids"].get<std::vector<int>>();
    }catch(const json::type_error& e)
    {
        std::cerr << "Type Error!" << e.what() << std::endl;
        return false;
    }
    return true;
}

int main()
{
    // 打开配置文件
    std::ifstream file("MyConfig.json");
    if(!file)
    {
        std::cerr << "Open ConfigFile Failed!" << std::endl;
        return 1;
    }
    // 解析
    json j;
    try{
        file >> j;
    }catch(const json::parse_error& e)
    {
        std::cerr << "Json Parse Error!" << e.what() << std::endl;
        return 1;
    }
    // 组装结构体
    JsonConfig cfg;
    if(!Json2Config(j, cfg))
        return 1;

    // 打印验证
    std::cout << "=== Server Configuration ===" << std::endl;
    std::cout << "Ip : " << cfg.ip << std::endl;
    std::cout << "Port : " << cfg.port << std::endl;
    std::cout << "PVP  : " << (cfg.pvp ? "ON" : "OFF") << std::endl;
    std::cout << "Login: ";
    for (int id : cfg.loginID) {
        std::cout << id << " ";
    }
    std::cout << "\n============================" << std::endl;

    // 修改保存
    cfg.maxPlayer = 1;
    cfg.pvp = false;
    j.clear();
    if(!Config2Json(cfg, j))
        return 1;
    std::ofstream newFile("new_config.json");
    if(!newFile)
    {
        std::cerr << "Open NewConfigFile Failed!" << std::endl;
        return 1;
    }
    newFile << j.dump(4);
    return 0;
}