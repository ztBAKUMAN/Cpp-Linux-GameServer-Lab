#include "ConfigManager.h"
#include <filesystem>

namespace fs = std::filesystem;

const std::string Default_Path = "MyConfig.json";

ConfigManager &ConfigManager::getInstance()
{
    static ConfigManager instance;
    return instance;
}

ConfigManager::ConfigManager()
{
    m_filepath = Default_Path;
    // 查看是否存在默认配置文件
    if(!fs::exists(Default_Path))
    {
        m_config = getDefaultConfig();
        saveConfig();
    }
    loadConfig(m_filepath);
}

void ConfigManager::setConfig(const JsonConfig &config)
{
    std::lock_guard<std::mutex> locker(m_mutex);
    m_config = config;
}

bool ConfigManager::loadConfig(const std::string &path)
{
    if (!path.empty() && path != m_filepath)
    {
        m_filepath = path;
    }

    // 判断文件格式
    if(!isJsonFile(m_filepath))
    {
        std::cerr << "It is not a JSON-formatted file!" << std::endl;
        return false;
    }

    // 判断路径存在
    fs::path parent_dir = fs::path(m_filepath).parent_path();
    if (!parent_dir.empty() && !fs::exists(parent_dir)) {
        std::cerr << parent_dir << " is not exists!" << std::endl;
        return false;
    }
    // 判断目标文件是否存在
    if (!fs::exists(m_filepath)){
        std::cerr << m_filepath << " is not exists!" << std::endl;
        return false;
    }

    // 打开文件
    std::ifstream loadFile(m_filepath);
    if (!loadFile.is_open())
    {
        std::cerr << "Open failed: " << m_filepath << std::endl;
        loadFile.close();
        return false;
    }
    // 解析文件
    json j;
    try{
        loadFile >> j;
    }catch(const json::parse_error& e)
    {
        std::cerr << "Json Parse Error!" << e.what() << std::endl;
        return false;
    }
    if(!Json2Config(j, m_config))
    {
        std::cerr << "Load configfile failed: " << std::endl;
        loadFile.close();
        return false;
    }
    std::cout << "Load configfile success!" << std::endl;
    loadFile.close();
    return true;
}

bool ConfigManager::saveConfig(const std::string &path)
{
    if (!path.empty() && path != m_filepath)
    {
        m_filepath = path;
    }

    // 判断文件格式
    if(!isJsonFile(m_filepath))
    {
        std::cerr << "It is not a JSON-formatted file!" << std::endl;
        return false;
    }

    // 判断路径存在
    fs::path parent_dir = fs::path(m_filepath).parent_path();
    
    if (!parent_dir.empty() && !fs::exists(parent_dir)) {
        std::cout << parent_dir << " is not exists! directory is creating..." << std::endl;

        if (fs::create_directories(parent_dir)) {
            std::cout << "Create directory success!" << std::endl;
        } else {
            std::cerr << "Create directory failed!" << std::endl;
            return false;
        }
    }

    // 打开文件(不存在默认创建, 存在则覆盖)
    std::ofstream newFile(m_filepath);
    if (!newFile.is_open())
    {
        std::cerr << "Open failed: " << m_filepath << std::endl;
        newFile.close();
        return false;
    }

    // 将最新配置数据存入文件
    json jsonData;
    if(!Config2Json(m_config, jsonData))
    {
        std::cerr << "Save configfile failed: " << std::endl;
        newFile.close();
        return false;
    }
    newFile << jsonData.dump(4);
    newFile.close();
    std::cout << "Save configfile success!" << std::endl;
    return true;
}

bool ConfigManager::isJsonFile(const std::string &file)
{
    // 是否为json格式
    // 获取后缀名
    std::string ext = fs::path(file).extension().string();
    // 转小写
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return (ext == ".json");
}

JsonConfig ConfigManager::getDefaultConfig()
{
    JsonConfig config;
    config.ip = "127.0.0.1";
    config.port = 8888;
    config.maxPlayer = 1000;
    config.pvp = true;
    config.loginID = {1000,2000,3000};
    return config;
}

bool ConfigManager::Config2Json(const JsonConfig &config, json &json)
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

bool ConfigManager::Json2Config(const json &j, JsonConfig &config)
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
