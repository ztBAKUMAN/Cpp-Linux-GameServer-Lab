#pragma once
#include <iostream>
#include <fstream>
#include <mutex>
#include <nlohmann/json.hpp>
#include "GlobalStruct.h"

// 设置nlohmann::json类的简称
using json = nlohmann::json;

// 使用单例模式创建配置管理类
class ConfigManager{
public:
    // 获取单例实例对象(static对象必须用static函数调用)
    static ConfigManager& getInstance();

    // 获取配置数据
    inline const JsonConfig& getConfig() const{return m_config;}

    // 设置配置数据
    void setConfig(const JsonConfig& config);

    // 加载配置
    bool loadConfig(const std::string& path);

    // 保存配置
    bool saveConfig(const std::string& path = "");

private:
    // 默认构造私有化
    ConfigManager();
    ~ConfigManager() = default;
    // 删除拷贝构造
    ConfigManager(const ConfigManager& obj) = delete;
    // 删除赋值拷贝
    ConfigManager& operator=(const ConfigManager& obj) = delete;

    // 判断文件路径是否合法(必须为.json文件)
    bool isJsonFile(const std::string& file);
    // 获取默认配置
    JsonConfig getDefaultConfig();
    // 将配置数据转为json
    bool Config2Json(const JsonConfig& config, json& json);
    // 将json转为配置数据
    bool Json2Config(const json& j, JsonConfig& config);

private:
    std::string m_filepath; // 配置路径
    JsonConfig m_config;    // 当前配置数据(全局唯一)
    std::mutex m_mutex;     // 使用成员变量锁保证线程读写安全
};